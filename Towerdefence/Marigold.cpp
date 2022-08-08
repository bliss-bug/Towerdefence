#include "Marigold.h"
#include "Shop.h"
#include <QGraphicsScene>

Marigold::Marigold() :Defender(300, 300, 0, 5, 50)
{
	cnt = 0;
	setMovie(":/image/Marigold.webp");
}

void Marigold::advance(int phase)
{
	if (phase == 0)
		return;
	update();
	if (hp <= 0)
	{
		state = 0;
		delete this;
		return;
	}

	Shop* shop = dynamic_cast<Shop*>(scene()->items(QPointF(13 * 90 + 50, 90))[0]);
	if (++cnt >= 400)
	{
		shop->addcoin(50);
		cnt = 0;
	}
}

void Marigold::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(0, -10, 60, 90), move->currentImage());

	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80, 10)));
	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80 * h / maxhp, 10)));
}