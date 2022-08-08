#include "FlyingEnemy1.h"

extern int killnum;

FlyingEnemy1::FlyingEnemy1(int p) :Enemy(400, 400, 0, 50.0 / 40, 30)
{
	road = p;
	setMovie(":/image/BalloonZombie.webp");
}

void FlyingEnemy1::advance(int phase)
{
	if (!phase)
		return;
	update();
	if (hp <= 0)
	{
		state = 0;
		killnum++;
		delete this;
		return;
	}
	Move();
}