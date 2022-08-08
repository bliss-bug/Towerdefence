#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

class Enemy :public QGraphicsItem
{
protected:
	QMovie* move;
	QMovie* head;
	double maxhp; //�������ֵ
	double hp; //��ǰ����ֵ
	double atk; //�����˺�
	double speed; //�ٶ�
	int road; //������·
	int index; //Ŀǰ�ڵ�·�ϵڼ�������
	int tp; //����
	int state; //״̬
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