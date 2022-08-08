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
	double maxhp; //�������ֵ
	double hp; //��ǰ����ֵ
	double atk; //�����˺�
	int cost; //����
	int tp; //����
	int state; //״̬
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