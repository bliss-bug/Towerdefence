#pragma once
#include "Defender.h"

class CherryBomb :public Defender
{
public:
	CherryBomb();
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void advance(int phase) override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};