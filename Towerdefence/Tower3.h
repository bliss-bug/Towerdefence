#pragma once
#include "Defender.h"

class Tower3 :public Defender
{
private:
	int cnt;
	int c;
public:
	Tower3();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void advance(int phase) override;
};