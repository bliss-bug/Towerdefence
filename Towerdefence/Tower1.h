#pragma once
#include "Defender.h"

class Tower1 :public Defender
{
private:
	int cnt;
	int t;
public:
	Tower1();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void advance(int phase) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};