#include "Defender.h"

int Defender::type() const
{
	return tp;
}

Defender::~Defender()
{
	if (move)
		delete move;
}

QRectF Defender::boundingRect() const
{
	return QRectF(0, 0, 60, 70);
}

void Defender::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//move->setCacheMode(QMovie::CacheAll);
	painter->drawImage(this->boundingRect(), move->currentImage());
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80, 10)));
	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-10, -15), QSize(80 * h / maxhp, 10)));
}

bool Defender::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() >= 20 && other->type() < 30 && qAbs(other->y() - y()) <= 50 && qAbs(other->x() - x()) <= 50;
}

void Defender::setMovie(QString p)
{
	if (move)
		delete move;
	move = new QMovie(p);
	move->start();
}

bool Defender::isdeath() const
{
	return hp <= 0;
}

void Defender::get_hurt(double val)
{
	hp -= val;
}

int Defender::getcost() const
{
	return cost;
}