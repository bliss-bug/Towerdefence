#pragma once
#include "Enemy.h"
#include "Path.h"

class GroundEnemy1 :public Enemy
{
public:
	GroundEnemy1(int p);
	void advance(int phase) override;
};