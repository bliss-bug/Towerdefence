#include "Radish.h"
#include <qdebug.h>

extern int killnum;

Radish::Radish()
{
	hp = 3;
}

int Radish::type() const
{
	return 40;
}

QRectF Radish::boundingRect() const
{
	return QRectF(0, 0, 70, 90);
}

void Radish::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QString index = QString::number(4 - hp, 10);
	painter->drawImage(this->boundingRect(), QImage(":/image/luobo" + index + ".png"));
	//qDebug() << hp;
}

bool Radish::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 40 && qAbs(other->y() - y()) <= 30 && qAbs(other->x() - x()) <= 30;
}

void Radish::advance(int phase)
{
	if (phase == 0)
		return;
	update();
	QList<QGraphicsItem*> items = collidingItems();
	if (!items.empty())
	{
		for(QGraphicsItem* item: items)
		{
			if (item->type() >= 20 && item->type() < 40 && hp >= 0)
			{
				hp--;
				delete item;
				killnum++;
			}
		}
	}
}

bool Radish::isdeath() const
{
	return hp <= 0;
}