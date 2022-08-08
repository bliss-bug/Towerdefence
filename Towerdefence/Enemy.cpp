#include "Enemy.h"
#include "Path.h"

extern Path path[3];

int Enemy::type() const
{
	return tp;
}

Enemy::~Enemy()
{
	if (move)
		delete move;
	if (head)
		delete head;
}

QRectF Enemy::boundingRect() const
{
	return QRectF(0, 0, 70, 90);
}

void Enemy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	//move->setCacheMode(QMovie::CacheAll);
	painter->drawImage(this->boundingRect(), move->currentImage());
	if(head)
		painter->drawImage(this->boundingRect(), head->currentImage());

	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::red);
	painter->drawRect(QRectF(QPoint(-5, 0), QSize(80, 10)));

	double h = hp >= 0 ? hp : 0;
	painter->setBrush(Qt::green);
	painter->drawRect(QRectF(QPoint(-5, 0), QSize(80 * h / maxhp, 10)));
}

bool Enemy::collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const
{
	return other->type() < 10 && other->type() != 1 && qAbs(other->y() - y()) <= 30 && qAbs(other->x() - x()) <= 30;
}

void Enemy::setMovie(QString p)
{
	if (move)
		delete move;
	move = new QMovie(p);
	move->start();
}

bool Enemy::isdeath() const
{
	return hp <= 0;
}

void Enemy::get_hurt(double val)
{
	hp -= val;
}

void Enemy::sethead(QString p)
{
	if (head)
		delete head;
	head = new QMovie(p);
	head->start();
}

void Enemy::Move()
{
	int x = path[road].p[index][0], y = path[road].p[index][1];
	double cx = 90 * x + 100, cy = 90 * y + 90;
	if (index < path[road].p.size() - 1)
	{
		int nx = path[road].p[index + 1][0], ny = path[road].p[index + 1][1];
		if (x == nx + 1)
		{
			setX(this->x() - speed);
			if (this->x() <= 100 + nx * 90)
				index++;
		}
		else if (y == ny + 1)
		{
			setY(this->y() - speed);
			if (this->y() <= 90 + ny * 90)
				index++;
		}
		else if (y == ny - 1)
		{
			setY(this->y() + speed);
			if (this->y() >= 90 + ny * 90)
				index++;
		}
		else
		{
			setX(this->x() + speed);
			if (this->x() >= 100 + nx * 90)
				index++;
		}
	}
	else
		setX(this->x() - speed);
}

void Enemy::restore_health(double val)
{
	hp = fmin(hp + val, maxhp);
}