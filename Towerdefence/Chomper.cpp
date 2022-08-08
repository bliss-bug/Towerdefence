#include "Chomper.h"
#include "Enemy.h"
#include <QGraphicsScene>

Chomper::Chomper() :Defender(300, 300, 60.0 / 40, 2, 100)
{
	setMovie(":/image/Chomper.gif");
	cnt = 0;
}

void Chomper::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(0, -15, 100, 90), move->currentImage());
	if (cnt <= 100)
	{
		painter->setPen(QColor(255, 207, 78));
		painter->drawEllipse(QPoint(30, 35), 130, 130);
		cnt++;
	}

	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-10, -10), QSize(80, 10)));
	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-10, -10), QSize(80 * h / maxhp, 10)));
}

bool Chomper::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 30 && qAbs(other->y() - y()) <= 130 && qAbs(other->x() - x()) <= 130
		&& QLineF(pos(), other->pos()).length() <= 130;
}

void Chomper::advance(int phase)
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
			setMovie(":/image/Chomper.gif");
			state = 1;
		}
	}
	else
	{
		if (state == 1)
		{
			state = 2;
			setMovie(":/image/ChomperAttack.gif");
		}
		else if (move->currentFrameNumber() == move->frameCount() - 1)
			setMovie(":/image/ChomperAttack.gif");
		for (QGraphicsItem* item : items)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(item);
			enemy->get_hurt(atk);
		}
	}
}

void Chomper::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	cnt = 0;
}