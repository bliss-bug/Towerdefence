#include "GroundEnemy4.h"
#include "Defender.h"
#include <QGraphicsScene>

extern int killnum;

GroundEnemy4::GroundEnemy4(int p) :Enemy(300, 300, 100.0 / 40, 45.0 / 40, 23)
{
	road = p;
	cnt = 0;
	setMovie(":/image/DancingZombieWalk.gif");
	buff = nullptr;
}

GroundEnemy4::~GroundEnemy4()
{
	if (buff)
		delete buff;
}

bool GroundEnemy4::collidesWithEnemy(const QGraphicsItem* other) const
{
	return other->type() >= 20 && other->type() < 40 && qAbs(x() - other->x()) <= 135 && qAbs(y() - other->y()) <= 135;
}

void GroundEnemy4::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(10, -5, 80, 100), move->currentImage());
	if (head)
		painter->drawImage(QRectF(20, 10, 80, 80), head->currentImage());

	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-5, 0), QSize(80, 10)));

	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-5, 0), QSize(80 * h / maxhp, 10)));

	if (buff)
		painter->drawImage(QRectF(-10, 0, 90, 90), *buff);
}

void GroundEnemy4::advance(int phase)
{
	if (!phase)
		return;
	update();
	if (hp <= 0)
	{
		if (state != 0)
		{
			state = 0;
			setMovie(":/image/DancingZombieDie.gif");
			sethead(":/image/DancingZombieHead.gif");
		}
		else if (move->currentFrameNumber() == move->frameCount() - 1)
		{
			killnum++;
			delete this;
		}
		return;
	}

	if (buff)
	{
		delete buff;
		buff = nullptr;
	}

	QList<QGraphicsItem*> items = collidingItems();
	if (!items.isEmpty())
	{
		QGraphicsItem* it = Q_NULLPTR;
		double mindis = 1e9;
		for (QGraphicsItem* item : items)
			if (QLineF(pos(), item->pos()).length() < mindis)
			{
				mindis = QLineF(pos(), item->pos()).length();
				it = item;
			}

		if (state != 2)
		{
			state = 2;
			setMovie(":/image/DancingZombieAttack.gif");
		}
		Defender* defender = dynamic_cast<Defender*>(it);
		defender->get_hurt(atk);
		return;
	}
	
	cnt++;
	QList<QGraphicsItem*> items2;
	for (QGraphicsItem* item : scene()->items())
		if (collidesWithEnemy(item))
			items2.append(item);
	if (cnt >= 100 && cnt < 200)
	{
		if (state != 3)
		{
			state = 3;
			setMovie(":/image/DancingZombieDancing.gif");
		}
		for (QGraphicsItem* item : items2)
		{
			Enemy* e = static_cast<Enemy*>(item);
			e->restore_health(1.5);
		}
		if (cnt < 116 || cnt >= 150 && cnt < 166)
			buff = new QImage(":/image/Heal_0.png");
		else if (cnt < 133 || cnt >= 166 && cnt < 183)
			buff = new QImage(":/image/Heal_1.png");
		else
			buff = new QImage(":/image/Heal_2.png");
	}
	else if (cnt >= 200)
	{
		cnt = 0;
		if (state != 1)
		{
			state = 1;
			setMovie(":/image/DancingZombieWalk.gif");
		}
	}
	Move();
}