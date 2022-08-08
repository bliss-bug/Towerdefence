#pragma once
#include "Defender.h"

class Spikeweed :public Defender
{
private:
	int cnt;
public:
	Spikeweed();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void advance(int phase) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};