#include "musclemap.h"

#include "qgraphicsmusclegroup.h"
#include "muscleencoding.h"

#include <QtWidgets>
#include <QtXml>
#include <QFile>

void MuscleMap::setUnselectedColor(QColor color) { unselectedColor = color; }
void MuscleMap::setSelectedColor(QColor color) { selectedColor = color; }
void MuscleMap::setBaseColor(QColor color) { baseColor = color; }

MuscleMap::MuscleMap() {
    selectionBits = 0;
    setSelectedColor(Qt::green);
    setUnselectedColor(Qt::lightGray);
    setBaseColor(Qt::red);

    setScene(&scene);
    setRenderHint(QPainter::Antialiasing);

    QDomDocument xml;
    QFile svgFile(":/Muscles-simplified.svg");
    if (!svgFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "Error", "Can't open SVG file for muscle diagram");
        return;
    }

    xml.setContent(&svgFile);
    svgFile.close();

    QDomElement root = xml.documentElement();

    QString type = root.tagName();
    if (root.tagName()!="svg") {
        QMessageBox::information(nullptr, "Error", "Invalid SVG file");
        return;
    }

    QString viewBox = root.attribute("viewBox", "");
    if (!viewBox.isEmpty()) {
        double x0, y0, x1, y1;
        QTextStream in(&viewBox);
        in >> x0 >> y0 >> x1 >> y1;
        x0 -= 10.0; y0 -= 10.0; x1 += 10.0; y1 += 10.0;
        setSceneRect(QRectF(x0, y0, x1-x0, y1-y0));
        resizeEvent(nullptr);
    }

    QDomElement elt = root.firstChildElement();
    if (elt.tagName()=="style") {
        QStringList styleList = elt.text().split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        foreach (QString s, styleList) {
            QStringList styleDef = s.split(QRegExp("[\\{\\}]"), Qt::SkipEmptyParts);
            if (styleDef.length()!=2) continue;
            QString styleName = styleDef[0].mid(1);
            QStringList props = styleDef[1].split(";", Qt::SkipEmptyParts);
            foreach (QString prop, props) {
                QStringList propDef = prop.split(":", Qt::SkipEmptyParts);
                if (propDef.length()!=2) continue;
                svgClasses[styleName][propDef[0]] = propDef[1];
            }
        }
    }
    svgClasses[""]["fill"] = "#000000";
    svgClasses[""]["stroke"] = "none";
    std::map<QString, int> idBits;
    idBits["front_delts"] = MuscleEncoding::Bit_Front_Deltoids;
    idBits["side_delts"] = MuscleEncoding::Bit_Side_Deltoids;
    idBits["rear_delts"] = MuscleEncoding::Bit_Rear_Deltoids;
    idBits["upper_pecs"] = MuscleEncoding::Bit_Upper_Chest;
    idBits["middle_pecs"] = MuscleEncoding::Bit_Middle_Chest;
    idBits["lower_pecs"] = MuscleEncoding::Bit_Lower_Chest;
    idBits["upper_traps"] = MuscleEncoding::Bit_Upper_Traps;
    idBits["upper_back"] = idBits["lower_traps"] = idBits["rhomboids"] = idBits["lats"] = MuscleEncoding::Bit_Upper_Back;
    idBits["lower_back"] = MuscleEncoding::Bit_Lower_Back;
    idBits["biceps"] = MuscleEncoding::Bit_Biceps;
    idBits["triceps"] = MuscleEncoding::Bit_Triceps;
    idBits["forearms"] = MuscleEncoding::Bit_Forearms;
    idBits["upper_abs"] = MuscleEncoding::Bit_Upper_Abs;
    idBits["lower_abs"] = MuscleEncoding::Bit_Lower_Abs;
    idBits["obliques"] = MuscleEncoding::Bit_Obliques;
    idBits["glutes"] = MuscleEncoding::Bit_Glutes;
    idBits["quads"] = MuscleEncoding::Bit_Quads;
    idBits["calves"] = MuscleEncoding::Bit_Calves;
    idBits["hamstrings"] = MuscleEncoding::Bit_Hamstrings;
    idBits["hip_abductor"] = MuscleEncoding::Bit_Hip_Abductor;
    idBits["hip_adductor"] = MuscleEncoding::Bit_Hip_Adductor;
    idBits["neck"] = MuscleEncoding::Bit_Neck;

    muscleGroups.resize(22, nullptr);

    while (true) {
        elt = elt.nextSiblingElement();
        if (elt.isNull()) break;

        if (elt.tagName()=="g") {
            QString groupName = elt.attribute("id", "");
            if (groupName.isEmpty()) continue;

            auto it = idBits.find(groupName);
            QGraphicsItemGroup *group;
            if (it!=idBits.end()) {
                if (muscleGroups[it->second]==nullptr) {
                    scene.addItem(muscleGroups[it->second] = new QGraphicsMuscleGroup(1 << it->second));
                    connect(muscleGroups[it->second], &QGraphicsMuscleGroup::pressed, this, &MuscleMap::muscleGroupPressed);
                }
                group = muscleGroups[it->second];
            } else {
                // qDebug() << "Skipped" << groupName;
                scene.addItem(group = new QGraphicsItemGroup());
            }

            if (svgGroups.find(groupName)!=svgGroups.end()) {
                int count = 1;
                while (svgGroups.find(groupName + "-" + QString::number(count))!=svgGroups.end())
                    ++count;
                groupName += QString("-") + QString::number(count);
            }

            QDomElement groupElement = elt.firstChildElement();
            while (!groupElement.isNull()) {
                if (groupElement.tagName()=="path") {
                    QString pathClass = groupElement.attribute("class", "");
                    QString d = groupElement.attribute("d", "").simplified();
                    d.replace(" ", "");
                    d.replace(QRegExp("([0-9])-"), "\\1,-");
                    if (!d.isEmpty() && svgClasses.find(pathClass)!=svgClasses.end()) {
                        QPainterPath path;
                        QTextStream in(&d);

                        while (!in.atEnd()) {
                            char ch;
                            QList<QPointF> points;
                            auto readPoints = [&in,&points](int n) {
                               points.clear();
                               double x, y;
                               char comma;
                               for (int i = 0; i < n; ++i) {
                                   if (i) in >> comma;
                                   in >> x >> comma >> y;
                                   points << QPointF(x,y);
                               }
                            };
                            in >> ch;
                            QPointF p0 = path.currentPosition();
                            if (ch=='z')
                                path.closeSubpath();
                            else if (ch=='M') {
                                readPoints(1);
                                path.moveTo(points[0]);
                            } else if (ch=='m') {
                                readPoints(1);
                                path.moveTo(p0+points[0]);
                            } else if (ch=='L') {
                                readPoints(1);
                                path.lineTo(points[0]);
                            } else if (ch=='l') {
                                readPoints(1);
                                path.lineTo(path.currentPosition()+points[0]);
                            } else if (ch=='H') {
                                double x; in >> x;
                                path.lineTo(x, p0.y());
                            } else if (ch=='h') {
                                double x; in >> x;
                                path.lineTo(p0.x() + x, p0.y());
                            } else if (ch=='V') {
                                double y; in >> y;
                                path.lineTo(p0.x(), y);
                            } else if (ch=='v') {
                                double y; in >> y;
                                path.lineTo(p0.x(), p0.y() + y);
                            } else if (ch=='C') {
                                readPoints(3);
                                path.cubicTo(points[0], points[1], points[2]);
                            } else if (ch=='c') {
                                readPoints(3);
                                path.cubicTo(p0+points[0], p0+points[1], p0+points[2]);
                            } else
                                qDebug() << "Unknown svg path-command " << ch;

                        }

                        QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
                        std::map<QString, QString> &classAttributes = svgClasses[pathClass];
                        bool stroked = false, filled = true;
                        QColor strokeColor, fillColor = "#000000";
                        double strokeWidth;
                        for (auto it : classAttributes) {
                            if (it.first=="fill") {
                                if (it.second=="none")
                                    filled = false;
                                else {
                                    fillColor = it.second;
                                    filled = true;
                                }
                            } else if (it.first=="stroke") {
                                if (it.second!="none") {
                                    stroked = true;
                                    strokeColor = it.second;
                                }
                            } else if (it.first=="stroke-width") {
                                stroked = true;
                                strokeWidth = it.second.toDouble();
                            }
                        }
                        if (stroked)
                            pathItem->setPen(QPen(strokeColor, strokeWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                        else
                            pathItem->setPen(Qt::NoPen);
                        if (filled)
                            pathItem->setBrush(fillColor);
                        else
                            pathItem->setBrush(Qt::NoBrush);

                        if (it!=idBits.end())
                            muscleGroups[it->second]->addPathItem(pathItem);
                        else
                            group->addToGroup(pathItem);
                    }
                }

                groupElement = groupElement.nextSiblingElement();
            }

            svgGroups[groupName] = group;
        }
    }
}

void MuscleMap::setMuscleGroupColors(int bits, QColor color) {
    for (int bit = 0; bit <= 21; ++bit)
        if (bits & (1 << bit) && muscleGroups[bit])
            muscleGroups[bit]->setColor(color);
}

void MuscleMap::setMuscleGroupBaseColors(int bits, QColor color) {
    for (int bit = 0; bit <= 21; ++bit)
        if (bits & (1 << bit) && muscleGroups[bit]) {
            muscleGroups[bit]->setBaseColor(color);
            muscleGroups[bit]->setColor(color);
        }
}

void MuscleMap::resizeEvent(QResizeEvent *) {
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void MuscleMap::muscleGroupPressed(int bits, bool shiftDown) {
    if (shiftDown)
        selectionBits ^= bits;
    else
        selectionBits = bits;
    updateSelection();
}

void MuscleMap::updateSelection() {
    if (selectionBits) {
        setMuscleGroupBaseColors(selectionBits, selectedColor);
        setMuscleGroupBaseColors(~selectionBits, unselectedColor);
    } else
        setMuscleGroupBaseColors(~0, baseColor);
    emit selectionChanged(selectionBits);
}

