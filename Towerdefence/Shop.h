#pragma once
#include "Icon.h"

class Shop :public QGraphicsItem
{
private:
	int coin;
	int cnt;
public:
	Shop();
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void advance(int phase) override;
	void AddDefender(QString s, QPointF pos);
	int get_coin() const;
	bool spend_coin(int cost);
	int type() const override;
	void addcoin(int num);
};