#include "GroundEnemy1.h"
#include "Defender.h"

extern int killnum;

GroundEnemy1::GroundEnemy1(int p) :Enemy(280, 280, 100.0 / 40, 40.0 / 40, 20)
{
	road = p;
	setMovie(":/image/ZombieWalk1.gif");
}

void GroundEnemy1::advance(int phase)
{
	if (!phase)
		return;
	update();
	if (hp <= 0)
	{
		if (state != 0)
		{
			state = 0;
			setMovie(":/image/ZombieDie.gif");
			sethead(":/image/ZombieHead.gif");
		}
		else if (move->currentFrameNumber() == move->frameCount() - 1)
		{
			killnum++;
			delete this;
		}
		return;
	}

	QList<QGraphicsItem*> items = collidingItems();
	if (items.empty())
	{
		if (state == 2)
		{
			state = 1;
			if (qrand() % 2 == 0)
				setMovie(":/image/ZombieWalk1.gif");
			else
				setMovie(":/image/ZombieWalk2.gif");
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
			setMovie(":/image/ZombieAttack.gif");
		}
		Defender* defender = dynamic_cast<Defender*>(it);
		defender->get_hurt(atk);
	}
}