#include "Map.h"
#include "Shovel.h"
#include <QMimeData>
#include <QGraphicsScene>

extern QVector<QVector<int>>cell;;

Map::Map()
{
	setAcceptDrops(true);
}

int Map::type() const
{
    return 43;
}

QRectF Map::boundingRect() const
{
	return QRectF(0, 0, 15 * 90, 10 * 90);
}

void Map::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
        update();
    }
    else
        event->setAccepted(false);
}

void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    update();
}

void Map::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->hasText())
    {
        QString s = event->mimeData()->text();
        QPointF pos = mapToScene(event->pos());
        int x = (int)pos.x() / 90 - 1, y = (int)pos.y() / 90 - 1;
        pos.setX(105 + 90 * x);
        pos.setY(100 + 90 * y);
        if (x < 0 || x > 11 || y < 0 || y > 7)
            goto out;
        if (s == "WallNut" || s == "Spikeweed" || s == "Chomper" || s == "BonkChoy" || s == "CherryBomb" || s == "Marigold")
        {
            if (cell[x][y] != 3 && cell[x][y] != 4)
                goto out;
            Shop* shop = qgraphicsitem_cast<Shop*>(scene()->items(QPointF(13 * 90 + 50, 90))[0]);
            shop->AddDefender(s, pos);
        }
        else if (s == "Tower1" || s == "Tower2" || s == "Tower3")
        {
            if (cell[x][y] != 5)
                goto out;
            Shop* shop = qgraphicsitem_cast<Shop*>(scene()->items(QPointF(13 * 90 + 50, 90))[0]);
            shop->AddDefender(s, pos);
        }
        else if (s == "Shovel")
        {
            Shovel* shovel = qgraphicsitem_cast<Shovel*>(scene()->items(QPointF(15 * 90 + 20, 90))[0]);
            shovel->RemoveDefender(pos);
        }
    }
    out:
    update();
}