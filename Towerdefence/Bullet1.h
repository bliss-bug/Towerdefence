#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "Enemy.h"

class Bullet1 :public QGraphicsItem
{
private:
	double atk;
	double x_speed;
	double y_speed;
public:
	Bullet1(double xp, double yp, int atk);
	int type() const override;
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void advance(int phase) override;
};