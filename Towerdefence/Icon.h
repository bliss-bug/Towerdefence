#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QHash>

class Icon :public QGraphicsItem
{
private:
	QString name;
public:
    const static QHash<QString, int>defcost;
	Icon(QString s) :name(s) {}
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    //void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    QString get_name() const;
    int type() const override;
};