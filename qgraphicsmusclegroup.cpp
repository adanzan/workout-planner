#include "qgraphicsmusclegroup.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>

void QGraphicsMuscleGroup::addPathItem(QGraphicsPathItem *item) {
    addToGroup(item);
    shapePath += item->path();
}

QGraphicsMuscleGroup::QGraphicsMuscleGroup(int _bits):muscleGroupBits(_bits),baseColor(Qt::red) {
    hoverColor = Qt::blue;
    setAcceptHoverEvents(true);
}

int QGraphicsMuscleGroup::bits() const { return muscleGroupBits; }

void QGraphicsMuscleGroup::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    setColor(hoverColor);
}

void QGraphicsMuscleGroup::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    setColor(baseColor);
}

void QGraphicsMuscleGroup::setBaseColor(QColor _baseColor) { baseColor = _baseColor; }
void QGraphicsMuscleGroup::setHoverColor(QColor _hoverColor) { hoverColor = _hoverColor; }

void QGraphicsMuscleGroup::setColor(QColor color) {
    QList<QGraphicsItem *> children = childItems();
    foreach (QGraphicsItem *child, children) {
        QGraphicsPathItem *pathItem = dynamic_cast<QGraphicsPathItem *>(child);
        if (pathItem!=nullptr) {
            pathItem->setPen(QPen(color, 10.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            pathItem->setBrush(color);
        }
    }
}

QPainterPath QGraphicsMuscleGroup::shape() const { return shapePath; }

void QGraphicsMuscleGroup::mousePressEvent(QGraphicsSceneMouseEvent *evt) {
    emit pressed(muscleGroupBits, evt->modifiers().testFlag(Qt::ShiftModifier));
}
