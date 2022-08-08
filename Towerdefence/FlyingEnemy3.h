#pragma once
#include "Enemy.h"
#include "Path.h"

class FlyingEnemy3:public Enemy
{
private:
	int cnt;
public:
	FlyingEnemy3(int p);
	void advance(int phase) override;
	bool collidesWithRemoteUnit(const QGraphicsItem* other) const;
};