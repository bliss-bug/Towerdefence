#pragma once
#include "Defender.h"

class Marigold :public Defender
{
private:
	int cnt;
public:
	Marigold();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void advance(int phase) override;
};