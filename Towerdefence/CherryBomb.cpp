#include "CherryBomb.h"
#include "Enemy.h"
#include <QGraphicsScene>

CherryBomb::CherryBomb() :Defender(300, 300, 1800, 4, 150)
{
	setMovie(":/image/CherryBomb.gif");
}

bool CherryBomb::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 40 && qAbs(other->y() - y()) <= 135 && qAbs(other->x() - x()) <= 135;
}

void CherryBomb::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (state == 1)
		painter->drawImage(QRectF(-15, 0, 90, 70), move->currentImage());
	else
		painter->drawImage(QRectF(-15, -15, 90, 100), move->currentImage());
	painter->setPen(QColor(255, 207, 78));
	painter->drawRect(QRectF(-105, -100, 270, 270));
}

void CherryBomb::advance(int phase)
{
	if (!phase)
		return;
	if (state == 0)
	{
		delete this;
		return;
	}
	update();

	QList<QGraphicsItem*> items;
	for (QGraphicsItem* item : scene()->items())
	{
		if (collidesWithItem(item, Qt::IntersectsItemShape))
			items.append(item);
	}
	if (state == 1)
	{
		if (move->currentFrameNumber() == move->frameCount() - 1)
		{
			setMovie(":/image/Boom.gif");
			state = 2;
		}
	}
	else
	{
		if (move->currentFrameNumber() == move->frameCount() - 1)
			state = 0;
		for (QGraphicsItem* item : items)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(item);
			enemy->get_hurt(this->atk);
		}
	}
}