#pragma once
#include "Enemy.h"
#include "Path.h"

class FlyingEnemy1 :public Enemy
{
public:
	FlyingEnemy1(int p);
	void advance(int phase) override;
};