#include "BonkChoy.h"
#include "Enemy.h"
#include <QGraphicsScene>

BonkChoy::BonkChoy() :Defender(300, 300, 65.0 / 40, 3, 150)
{
	setMovie(":/image/BonkChoy.webp");
	cnt = 0;
}

bool BonkChoy::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 40 && qAbs(other->y() - y()) <= 135 && qAbs(other->x() - x()) <= 135
		&& QLineF(pos(),other->pos()).length() <= 135;
}


void BonkChoy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (state == 1)
		painter->drawImage(QRectF(-15, 0, 90, 70), move->currentImage());
	else
		painter->drawImage(QRectF(-30, -80, 180, 180), move->currentImage());
	if (cnt <= 100)
	{
		painter->setPen(QColor(255, 207, 78));
		painter->drawEllipse(QPoint(30, 35), 135, 135);
		cnt++;
	}

	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-10, -10), QSize(80, 10)));
	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-10, -10), QSize(80 * h / maxhp, 10)));
}

void BonkChoy::advance(int phase)
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

	QList<QGraphicsItem*> items;
	for (QGraphicsItem* item : scene()->items())
	{
		if (collidesWithItem(item, Qt::IntersectsItemShape))
			items.append(item);
	}
	if (items.empty())
	{
		if (state == 2)
		{
			setMovie(":/image/BonkChoy.webp");
			state = 1;
		}
	}
	else
	{
		if (state == 1)
		{
			state = 2;
			setMovie(":/image/BonkChoy.gif");
		}
		for (QGraphicsItem* item : items)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(item);
			enemy->get_hurt(atk);
		}
	}
}

void BonkChoy::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	cnt = 0;
}