#include "Tower3.h"
#include "Tower1.h"
#include "Tower2.h"
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsItem>

extern QVector<QVector<int>>remotecell;

Tower3::Tower3() :Defender(500, 500.0, 0, 12, 250)
{
	cnt = 0;
	c = 0;
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	setMovie(":/image/Tower3.png");
}

void Tower3::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(-10, -5, 80, 80), move->currentImage());
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80, 10)));
	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80 * h / maxhp, 10)));
}

void Tower3::advance(int phase)
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

	if (++cnt >= 600)
	{
		cnt = 0;
		c = 0;
		begin:
		int ran = qrand() % 3;
		int index = qrand() % remotecell.size();
		Defender* tower = Q_NULLPTR;
		double x = remotecell[index][0] * 90 + 105;
		double y = remotecell[index][1] * 90 + 100;

		QList<QGraphicsItem*> items = scene()->items(QPointF(x, y), Qt::IntersectsItemBoundingRect);
		for (QGraphicsItem* item : items)
			if (item->type() >= 10 && item->type() < 20)
			{
				if (++c > 3)
					return;
				else
					goto begin;
			}

		if (ran < 2)
			tower = new Tower1;
		else
			tower = new Tower2;
		tower->setPos(QPointF(x, y));
		scene()->addItem(tower);
	}
}