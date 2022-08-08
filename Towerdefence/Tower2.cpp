#include "Tower2.h"
#include "Enemy.h"
#include "Bullet2.h"
#include <QGraphicsScene>

Tower2::Tower2() :Defender(500, 500.0, 25.0, 11, 200)
{
	cnt = 0;
	t = 0;
	setMovie(":/image/Tower2.png");
}

void Tower2::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(-10, -5, 80, 80), move->currentImage());
	if (t <= 100)
	{
		painter->setPen(QColor(101, 255, 223));
		painter->drawEllipse(QPoint(30, 35), 540, 540);
		t++;
	}
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80, 10)));
	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80 * h / maxhp, 10)));
}

bool Tower2::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 40 && QLineF(pos(), other->pos()).length() <= 540;
}

void Tower2::advance(int phase)
{
	if (!phase)
		return;
	update();
	if (hp <= 0)
	{
		state = 0;
		delete this;
		return;
	}

	if (++cnt >= 20)
	{
		cnt = 0;
		QList<QGraphicsItem*> items;
		for (QGraphicsItem* item : scene()->items())
		{
			if (collidesWithItem(item, Qt::IntersectsItemShape))
				items.append(item);
		}

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
			Enemy* enemy = dynamic_cast<Enemy*>(it);
			if (enemy)
			{
				double x_speed = 20.0 * (enemy->x() - x()) / sqrt(pow(enemy->x() - x(), 2) + pow(enemy->y() - y(), 2));
				double y_speed = 20.0 * (enemy->y() - y()) / sqrt(pow(enemy->x() - x(), 2) + pow(enemy->y() - y(), 2));
				Bullet2* bullet2 = new Bullet2(x_speed, y_speed, atk);
				bullet2->setPos(pos());
				scene()->addItem(bullet2);
			}
		}
	}
}

void Tower2::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	t = 0;
}