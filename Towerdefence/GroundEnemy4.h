#pragma once
#include "Enemy.h"
#include "Path.h"

class GroundEnemy4 :public Enemy
{
private:
	int cnt;
	QImage* buff;
public:
	GroundEnemy4(int p);
	~GroundEnemy4();
	void advance(int phase) override;
	bool collidesWithEnemy(const QGraphicsItem* other) const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};