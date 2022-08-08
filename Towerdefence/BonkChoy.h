#pragma once
#include "Defender.h"

class BonkChoy :public Defender
{
private:
	int cnt;
public:
	BonkChoy();
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	//QRectF boundingRect() const override;
	void advance(int phase) override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};