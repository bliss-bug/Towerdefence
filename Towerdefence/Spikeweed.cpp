#include "Spikeweed.h"
#include "Enemy.h"

Spikeweed::Spikeweed() :Defender(1000, 1000, 28.0 / 40, 1, 100)
{
	setMovie(":/image/Spikeweed.gif");
	cnt = 0;
}

void Spikeweed::advance(int phase)
{
	if (phase == 0)
		return;
	update();

	QList<QGraphicsItem*> items = collidingItems();
	for (auto item : items)
	{
		Enemy* e = dynamic_cast<Enemy*>(item);
		e->get_hurt(atk);
	}
}

void Spikeweed::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(-10, 50, 80, 25), move->currentImage());
	if (cnt <= 100)
	{
		painter->setPen(QColor(103, 255, 252));
		painter->drawRect(QRectF(-20, -15, 100, 100));
		cnt++;
	}
}

void Spikeweed::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	cnt = 0;
}