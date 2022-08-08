#pragma once
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>

class Shovel :public QGraphicsItem
{
public:
    Shovel() {}
	int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void RemoveDefender(QPointF pos);
};