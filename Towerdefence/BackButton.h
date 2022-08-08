#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QSound>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

class BackButton :public QGraphicsItem
{
public:
	BackButton();
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};