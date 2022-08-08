#include <QGraphicsScene>
#include "Shop.h"
#include "GroundEnemy1.h"
#include "FlyingEnemy1.h"
#include "Wallnut.h"
#include "Spikeweed.h"
#include "Chomper.h"
#include "CherryBomb.h"
#include "BonkChoy.h"
#include "Marigold.h"
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"

extern QVector<QVector<int>>cell;;

Shop::Shop()
{
	coin = 100;
	cnt = 0;
	int i = 0;
	Icon* icon1 = new Icon("WallNut");
	icon1->setParentItem(this);
	icon1->setPos(10, 100);

	Icon* icon2 = new Icon("Spikeweed");
	icon2->setParentItem(this);
	icon2->setPos(160, 100);

	Icon* icon3 = new Icon("Chomper");
	icon3->setParentItem(this);
	icon3->setPos(10, 250);

	Icon* icon4 = new Icon("BonkChoy");
	icon4->setParentItem(this);
	icon4->setPos(160, 250);

	Icon* icon5 = new Icon("CherryBomb");
	icon5->setParentItem(this);
	icon5->setPos(10, 400);

	Icon* icon6 = new Icon("Marigold");
	icon6->setParentItem(this);
	icon6->setPos(160, 400);

	Icon* icon7 = new Icon("Tower1");
	icon7->setParentItem(this);
	icon7->setPos(10, 550);

	Icon* icon8 = new Icon("Tower2");
	icon8->setParentItem(this);
	icon8->setPos(160, 550);

	Icon* icon9 = new Icon("Tower3");
	icon9->setParentItem(this);
	icon9->setPos(10, 700);
}

QRectF Shop::boundingRect() const
{
	return QRectF(0, 0, 300, 1000);
}

int Shop::type() const
{
	return 41;
}

int Shop::get_coin() const
{
	return coin;
}

bool Shop::spend_coin(int cost)
{
	if (coin < cost)
		return false;
	coin -= cost;
	return true;
}

void Shop::advance(int phase)
{
	if (phase == 0)
		return;
	update();
	if (++cnt == 400)
	{
		cnt = 0;
		coin += 50;
	}
}

void Shop::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(QRectF(0, 0, 35, 56), QImage(":/image/money2.png"));
	QFont font;
	font.setPointSizeF(20);
	painter->setFont(font);
	painter->drawText(QRectF(30, -5, 90, 60), Qt::AlignCenter, QString::number(coin));
}

void Shop::AddDefender(QString s, QPointF pos)
{
	QList<QGraphicsItem*> items = scene()->items(pos, Qt::IntersectsItemBoundingRect);
	for (QGraphicsItem* item : items)
		if (item->type() >= 0 && item->type() < 20)
			return;

	Defender* defender = Q_NULLPTR;
	if (s == "WallNut")
		defender = new Wallnut;
	else if (s == "Spikeweed")
		defender = new Spikeweed;
	else if (s == "Chomper")
		defender = new Chomper;
	else if (s == "BonkChoy")
		defender = new BonkChoy;
	else if (s == "CherryBomb")
		defender = new CherryBomb;
	else if (s == "Marigold")
		defender = new Marigold;
	else if (s == "Tower1")
		defender = new Tower1;
	else if (s == "Tower2")
		defender = new Tower2;
	else if (s == "Tower3")
		defender = new Tower3;

	defender->setPos(pos);
	scene()->addItem(defender);
	coin -= Icon::defcost[s];
}

void Shop::addcoin(int num)
{
	coin += num;
}