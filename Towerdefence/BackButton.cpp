#include "BackButton.h"

extern int creatednum;
extern int killnum;
extern int curtime;

BackButton::BackButton(){}

QRectF BackButton::boundingRect() const
{
	return QRectF(0, 0, 100, 100);
}

void BackButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(boundingRect(), QImage(":/image/ButtonBack.png"));
}
