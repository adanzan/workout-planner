#ifndef MUSCLEMAP_H
#define MUSCLEMAP_H

#include <QGraphicsView>

#include <map>

class QGraphicsMuscleGroup;

class MuscleMap : public QGraphicsView {
    Q_OBJECT

    QGraphicsScene scene;
    std::map<QString, std::map<QString, QString> > svgClasses;
    std::map<QString, QGraphicsItemGroup *> svgGroups;
    std::vector<QGraphicsMuscleGroup *> muscleGroups;

    QColor selectedColor, unselectedColor;
    QColor baseColor;
    int selectionBits;

public:
    MuscleMap();
    void setMuscleGroupColors(int bits, QColor color);
    void setMuscleGroupBaseColors(int bits, QColor color);
    void setSelectedColor(QColor color);
    void setUnselectedColor(QColor color);
    void setBaseColor(QColor color);
    void updateSelection();

public slots:
    void muscleGroupPressed(int bits, bool shiftDown);

protected:
    void resizeEvent(QResizeEvent *evt) override;

signals:
    void selectionChanged(int bits);
};

#endif // MUSCLEMAP_H
