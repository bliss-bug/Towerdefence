#include "FlyingEnemy3.h"
#include "Defender.h"
#include "LaserBullet.h"
#include <QGraphicsScene>

extern int killnum;

FlyingEnemy3::FlyingEnemy3(int p) :Enemy(300, 300, 100.0 / 40, 45.0 / 40, 32)
{
	cnt = 0;
	road = p;
	setMovie(":/image/BalloonZombie3.webp");
}

bool FlyingEnemy3::collidesWithRemoteUnit(const QGraphicsItem* other) const
{
	return other->type() >= 10 && other->type() < 20 && QLineF(pos(), other->pos()).length() <= 360;
}

void FlyingEnemy3::advance(int phase)
{
	if (phase == 0)
		return;
	if (hp <= 0)
	{
		state = 0;
		killnum++;
		delete this;
		return;
	}

	QList<QGraphicsItem*> items1 = collidingItems();
	if (!items1.isEmpty())
	{
		state = 2;
		QGraphicsItem* it = Q_NULLPTR;
		double mindis = 1e9;
		for (QGraphicsItem* item : items1)
			if (QLineF(pos(), item->pos()).length() < mindis)
			{
				mindis = QLineF(pos(), item->pos()).length();
				it = item;
			}
		Defender* defender = dynamic_cast<Defender*>(it);
		defender->get_hurt(atk);
		return;
	}

	QList<QGraphicsItem*> items2;
	for (QGraphicsItem* item : scene()->items())
		if (collidesWithRemoteUnit(item))
			items2.append(item);

	if (!items2.isEmpty())
	{
		if (++cnt >= 30)
		{
			cnt = 0;
			state = 3;
			QGraphicsItem* it = Q_NULLPTR;
			double mindis = 1e9;
			for (QGraphicsItem* item : items2)
				if (QLineF(pos(), item->pos()).length() < mindis)
				{
					mindis = QLineF(pos(), item->pos()).length();
					it = item;
				}
			Defender* defender = dynamic_cast<Defender*>(it);
			if (defender)
			{
				double x_speed = 15.0 * (defender->x() - x()) / sqrt(pow(defender->x() - x(), 2) + pow(defender->y() - y(), 2));
				double y_speed = 15.0 * (defender->y() - y()) / sqrt(pow(defender->x() - x(), 2) + pow(defender->y() - y(), 2));
				LaserBullet* bullet = new LaserBullet(x_speed, y_speed, 30.0);
				bullet->setPos(pos());
				scene()->addItem(bullet);
			}
		}
		Move();
	}
	else
	{
		state = 1;
		Move();
	}
}