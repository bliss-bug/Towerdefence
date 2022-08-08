#include "GroundEnemy3.h"
#include "Defender.h"
#include "LaserBullet.h"
#include <QGraphicsScene>

extern int killnum;

GroundEnemy3::GroundEnemy3(int p) :Enemy(300, 300, 100.0 / 40, 45.0 / 40, 22)
{
	road = p;
	cnt = 0;
	setMovie(":/image/BoxZombieWalk.gif");
}

QRectF GroundEnemy3::boundingRect() const
{
	return QRectF(-40, -7, 100, 100);
}

bool GroundEnemy3::collidesWithRemoteUnit(const QGraphicsItem* other) const
{
	return other->type() >= 10 && other->type() < 20 && QLineF(pos(), other->pos()).length() <= 450;
}

void GroundEnemy3::advance(int phase)
{
	if (!phase)
		return;
	update();
	if (hp <= 0)
	{
		if (state != 0)
		{
			state = 0;
			setMovie(":/image/BoxZombieDie.gif");
			sethead(":/image/ZombieHead.gif");
		}
		else if (move->currentFrameNumber() == move->frameCount() - 1)
		{
			killnum++;
			delete this;
		}
		return;
	}

	QList<QGraphicsItem*> items1 = collidingItems();
	if (!items1.isEmpty())
	{
		if (state != 2)
		{
			state = 2;
			setMovie(":/image/BoxZombieAttack.gif");
		}
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

	if (!items2.empty())
	{
		if (state != 3)
		{
			state = 3;
			setMovie(":/image/BoxZombieAttack2.gif");
		}
		if (++cnt >= 30)
		{
			cnt = 0;
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
		return;
	}

	if (state != 1)
	{
		state = 1;
		setMovie(":/image/BoxZombieWalk.gif");
	}
	Move();
}