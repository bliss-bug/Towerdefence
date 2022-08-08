#include "GroundEnemy2.h"
#include "Defender.h"
#include <QGraphicsScene>

extern int killnum;

GroundEnemy2::GroundEnemy2(int p) :Enemy(270, 270, 80.0 / 40, 60.0 / 40, 21)
{
	road = p;
	setMovie(":/image/MagicZombieWalk.gif");
}

bool GroundEnemy2::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	//qDebug() << other->type();
	return other->type() < 10 && other->type() != 1 && qAbs(other->y() - y()) <= 240 &&
		other->x() - x() <= 30 && other->x() - x() >= -240 && QLineF(pos(), other->pos()).length() <= 240;
}

void GroundEnemy2::advance(int phase)
{
	if (!phase)
		return;
	update();
	if (hp <= 0)
	{
		if (state != 0)
		{
			state = 0;
			setMovie(":/image/MagicZombieDie.gif");
		}
		else if (move->currentFrameNumber() == move->frameCount() - 1)
		{
			killnum++;
			delete this;
		}
		return;
	}

	QList<QGraphicsItem*> items;
	for (QGraphicsItem* item : scene()->items())
	{
		if (collidesWithItem(item, Qt::IntersectsItemShape))
			items.append(item);
	}
	
	if (items.isEmpty())
	{
		if (state == 2)
		{
			state = 1;
			setMovie(":/image/MagicZombieWalk.gif");
		}
		Move();
	}
	else
	{
		QGraphicsItem* it = Q_NULLPTR;
		double mindis = 1e9;
		for(QGraphicsItem* item:items)
			if (QLineF(pos(), item->pos()).length() < mindis)
			{
				mindis = QLineF(pos(), item->pos()).length();
				it = item;
			}

		if (state == 1)
		{
			state = 2;
			setMovie(":/image/MagicZombieAttack.gif");
		}
		Defender* defender = dynamic_cast<Defender*>(it);
		defender->get_hurt(atk);
	}
}