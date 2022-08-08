#pragma once
#include <QGraphicsSceneDragDropEvent>
#include "Shop.h"
#include "Defender.h"

class Map :public QGraphicsItem
{
public:
	Map();
    int type() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {}
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
};