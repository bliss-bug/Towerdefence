#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <qdebug.h>

class Defender :public QGraphicsItem
{
protected:
	QMovie* move;
	double maxhp; //最大生命值
	double hp; //当前生命值
	double atk; //攻击伤害
	int cost; //花费
	int tp; //类型
	int state; //状态
public:
	Defender(double m, double h, double a, int t, int c) :move(Q_NULLPTR), maxhp(m), hp(h), atk(a), tp(t), state(1), cost(c) {}
	virtual ~Defender();
	int type() const override;
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void setMovie(QString p);
	bool isdeath() const;
	void get_hurt(double val);
	int getcost() const;
};