#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QString>
#include "Enemy.h"

class Radish :public QGraphicsItem
{
private:
	int hp;
public:
	Radish();
	QRectF boundingRect() const override;
	int type() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void advance(int phase) override;
	bool isdeath() const;
};