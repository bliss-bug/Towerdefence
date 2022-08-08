#pragma once
#include "Enemy.h"
#include "Path.h"

class FlyingEnemy2 :public Enemy
{
public:
	FlyingEnemy2(int p);
	void advance(int phase) override;
};