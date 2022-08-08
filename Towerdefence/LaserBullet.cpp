#include "LaserBullet.h"
#include <QGraphicsScene>

LaserBullet::LaserBullet(double xp, double yp, int a) :x_speed(xp), y_speed(yp), atk(a) {}

int LaserBullet::type() const
{
	return 47;
}

QRectF LaserBullet::boundingRect() const
{
	return QRectF(30, 35, 20, 20);
}

void LaserBullet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(this->boundingRect(), QImage(":/image/LaserBullet.png"));
}

bool LaserBullet::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 10 && other->type() < 20 && qAbs(other->y() - y()) <= 30 && qAbs(other->x() - x()) <= 20;
}

void LaserBullet::advance(int phase)
{
	if (!phase)
		return;
	update();

	QList<QGraphicsItem*> items = collidingItems();
	if (!items.empty())
	{
		QGraphicsItem* it = Q_NULLPTR;
		double mindis = 1e9;
		for (QGraphicsItem* item : items)
			if (QLineF(pos(), item->pos()).length() < mindis)
			{
				mindis = QLineF(pos(), item->pos()).length();
				it = item;
			}
		Defender* defender = dynamic_cast<Defender*>(it);
		defender->get_hurt(atk);
		delete this;
	}
	else
	{
		setX(x() + x_speed);
		setY(y() + y_speed);
		if (x() > 13 * 90 || x() < 90 || y() > 9 * 90 || y() < 90)
			delete this;
	}
}