#include "Icon.h"
#include "Shop.h"
#include <QString>
#include <QtWidgets>

const QHash<QString, int>Icon::defcost = { {"WallNut",50},{"Spikeweed",100},{"Chomper",100},{"BonkChoy",150},
                                        {"CherryBomb",150},{"Marigold",50}, {"Tower1",100}, {"Tower2",200},{"Tower3",250} };

QString Icon::get_name() const
{
	return name;
}

QRectF Icon::boundingRect() const
{
	return QRectF(0, 0, 80, 100);
}

int Icon::type() const
{
	return 42;
}

void Icon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (name == "WallNut")
        painter->drawImage(QRectF(0, 20, 70, 80), QImage(":/image/WallNut.png"));
    else if (name == "Spikeweed")
        painter->drawImage(QRectF(0, 60, 90, 30), QImage(":/image/Spikeweed.png"));
    else if (name == "Chomper")
        painter->drawImage(QRectF(-15, 0, 130, 110), QImage(":/image/Chomper.png"));
    else if (name == "BonkChoy")
        painter->drawImage(QRectF(-10, 10, 120, 100), QImage(":/image/BonkChoy.png"));
    else if (name == "CherryBomb")
        painter->drawImage(QRectF(-10, 25, 100, 80), QImage(":/image/CherryBomb.png"));
    else if (name == "Marigold")
        painter->drawImage(QRectF(10, 0, 80, 110), QImage(":/image/Marigold.png"));
    else if (name == "Tower1")
        painter->drawImage(QRectF(-10, 20, 100, 100), QImage(":/image/Tower1Icon.png"));
    else if (name == "Tower2")
        painter->drawImage(QRectF(0, 20, 100, 100), QImage(":/image/Tower2Icon.png"));
    else if (name == "Tower3")
        painter->drawImage(QRectF(-15, 20, 100, 100), QImage(":/image/Tower3.png"));
}

void Icon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Shop* shop = qgraphicsitem_cast<Shop*>(parentItem());
    if (defcost[name] > shop->get_coin())
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);
}

void Icon::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
        return;
    QDrag* drag = new QDrag(event->widget());
    QMimeData* mime = new QMimeData;
    QImage image(":/image/" + name + ".gif");
    mime->setText(name);
    mime->setImageData(image);
    drag->setMimeData(mime);
    if (name == "BonkChoy")
        drag->setPixmap(QPixmap::fromImage(image).scaled(180, 180));
    else if (name == "Chomper")
        drag->setPixmap(QPixmap::fromImage(image));
    else if (name == "Marigold")
        drag->setPixmap(QPixmap(":/image/Marigold.webp").scaled(70, 100));
    else if (name == "Tower1")
        drag->setPixmap(QPixmap(":/image/Tower1.png").scaled(80, 80));
    else if (name == "Tower2")
        drag->setPixmap(QPixmap(":/image/Tower2.png").scaled(80, 80));
    else if (name == "Tower3")
        drag->setPixmap(QPixmap(":/image/Tower3.png").scaled(80, 80));
    else
        drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(30, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Icon::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    setCursor(Qt::ArrowCursor);
}