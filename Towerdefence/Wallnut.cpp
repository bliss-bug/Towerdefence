#include "Wallnut.h"
#include "Enemy.h"

Wallnut::Wallnut() :Defender(3000, 3000, 0, 0, 50)
{
	setMovie(":/image/WallNut.gif");
}

void Wallnut::advance(int phase)
{
	if (phase == 0)
		return;
	update();
	if (hp <= 0)
	{
		state = 0;
		delete this;
		return;
	}

	if (hp > 2000);
	else if (hp > 1000)
	{
		if (state != 2)
		{
			state = 2;
			setMovie(":/image/WallNut1.gif");
		}
	}
	else
	{
		if (state != 3)
		{
			state = 3;
			setMovie(":/image/WallNut2.gif");
		}
	}
}