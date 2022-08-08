#pragma once
#include "Enemy.h"
#include "Path.h"

class GroundEnemy2 :public Enemy
{
public:
	GroundEnemy2(int p);
	void advance(int phase) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
};