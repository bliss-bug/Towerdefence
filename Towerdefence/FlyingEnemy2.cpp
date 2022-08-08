#include "FlyingEnemy2.h"
#include "Defender.h"

extern int killnum;

FlyingEnemy2::FlyingEnemy2(int p) :Enemy(300, 300, 100.0 / 40, 45.0 / 40, 31)
{
	road = p;
	setMovie(":/image/BalloonZombie2.webp");
}

void FlyingEnemy2::advance(int phase)
{
	if (phase == 0)
		return;
	update();
	if (hp <= 0)
	{
		state = 0;
		killnum++;
		delete this;
		return;
	}

	QList<QGraphicsItem*> items = collidingItems();
	if (items.isEmpty())
	{
		if (state == 2)
		{
			state = 1;
		}
		Move();
	}
	else
	{
		QGraphicsItem* it = Q_NULLPTR;
		double mindis = 1e9;
		for (QGraphicsItem* item : items)
			if (QLineF(pos(), item->pos()).length() < mindis)
			{
				mindis = QLineF(pos(), item->pos()).length();
				it = item;
			}

		if (state == 1)
		{
			state = 2;
		}
		Defender* defender = dynamic_cast<Defender*>(it);
		defender->get_hurt(atk);
	}
}