#include "Bullet2.h"
#include "Enemy.h"
#include <QGraphicsScene>

Bullet2::Bullet2(double xp, double yp, int a) :x_speed(xp), y_speed(yp), atk(a) {}

int Bullet2::type() const
{
	return 46;
}

QRectF Bullet2::boundingRect() const
{
	return QRectF(25, 25, 23, 23);
}

void Bullet2::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(this->boundingRect(), QImage(":/image/Tower2Bullet.png"));
}

bool Bullet2::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 40 && qAbs(other->y() - y()) <= 30 && qAbs(other->x() - x()) <= 20;
}

void Bullet2::advance(int phase)
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
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		enemy->get_hurt(atk);
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