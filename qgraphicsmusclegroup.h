#ifndef QGRAPHICSMUSCLEGROUP_H
#define QGRAPHICSMUSCLEGROUP_H

#include <QGraphicsItemGroup>

class QGraphicsMuscleGroup : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

    int muscleGroupBits;
    QColor baseColor, hoverColor;
    QPainterPath shapePath;

public:
    QGraphicsMuscleGroup(int _bits);
    void setBaseColor(QColor color);
    void setHoverColor(QColor color);
    void setColor(QColor color);
    void addPathItem(QGraphicsPathItem *item);
    int bits() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *evt) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *evt) override;
    QPainterPath shape() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *evt) override;

signals:
    void pressed(int bits, bool shiftDown);
};

#endif // QGRAPHICSMUSCLEGROUP_H
