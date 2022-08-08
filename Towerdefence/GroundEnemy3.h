#pragma once
#include "Enemy.h"
#include "Path.h"

class GroundEnemy3 :public Enemy
{
private:
	int cnt;
public:
	GroundEnemy3(int p);
	QRectF boundingRect() const override;
	void advance(int phase) override;
	bool collidesWithRemoteUnit(const QGraphicsItem* other) const;
};