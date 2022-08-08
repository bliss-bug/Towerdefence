#pragma once
#include "Defender.h"

class Chomper :public Defender
{
private:
	int cnt;
public:
	Chomper();
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void advance(int phase) override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};