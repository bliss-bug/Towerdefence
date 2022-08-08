#include "Tower1.h"
#include "Enemy.h"
#include "Bullet1.h"
#include <QGraphicsScene>

Tower1::Tower1() :Defender(400, 400.0, 20.0, 10, 100)
{
	cnt = 0;
	t = 0;
	setMovie(":/image/Tower1.png");
}

void Tower1::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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

bool Tower1::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 30 && QLineF(pos(), other->pos()).length() <= 540;
}

void Tower1::advance(int phase)
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
				Bullet1* bullet1 = new Bullet1(x_speed, y_speed, atk);
				bullet1->setPos(pos());
				scene()->addItem(bullet1);
			}
		}
	}
}

void Tower1::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	t = 0;
}