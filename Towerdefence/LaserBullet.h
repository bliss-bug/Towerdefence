#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "Defender.h"

class LaserBullet :public QGraphicsItem
{
private:
	double atk;
	double x_speed;
	double y_speed;
public:
	LaserBullet(double xp, double yp, int atk);
	int type() const override;
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void advance(int phase) override;
};