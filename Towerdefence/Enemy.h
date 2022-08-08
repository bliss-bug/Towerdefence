#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

class Enemy :public QGraphicsItem
{
protected:
	QMovie* move;
	QMovie* head;
	double maxhp; //最大生命值
	double hp; //当前生命值
	double atk; //攻击伤害
	double speed; //速度
	int road; //哪条道路
	int index; //目前在道路上第几个格子
	int tp; //类型
	int state; //状态
public:
	Enemy(double m, double h, double a, double s, int t) :move(Q_NULLPTR), head(Q_NULLPTR), 
		hp(h), atk(a), speed(s), tp(t), maxhp(m), state(1), index(0), road(0) {}
	virtual ~Enemy();
	int type() const override;
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	bool collidesWithItem(const QGraphicsItem* other, Qt::ItemSelectionMode mode) const override;
	void setMovie(QString p);
	void sethead(QString p);
	bool isdeath() const;
	void get_hurt(double val);
	void Move();
	void restore_health(double val);
};