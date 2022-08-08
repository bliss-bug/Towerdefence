#include "Shovel.h"
#include "Defender.h"

int Shovel::type() const
{
	return 44;
}

QRectF Shovel::boundingRect() const
{
	return QRectF(0, 0, 90, 90);
}

void Shovel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->drawImage(this->boundingRect(), QImage(":/image/Shovel.png"));
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	setCursor(Qt::ArrowCursor);
}

void Shovel::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
		return;
	QDrag* drag = new QDrag(event->widget());
	QMimeData* mime = new QMimeData;
	mime->setText("Shovel");
	mime->setImageData(QImage(":/image/Shovel.png"));
	drag->setMimeData(mime);
	drag->setPixmap(QPixmap(":/image/Shovel.png").scaled(70, 70));
	drag->setHotSpot(QPoint(35, 35));
	drag->exec();
	setCursor(Qt::ArrowCursor);
}

void Shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	setCursor(Qt::ArrowCursor);
}

void Shovel::RemoveDefender(QPointF pos)
{
	QList<QGraphicsItem*> items = scene()->items(pos);
	for(QGraphicsItem* item:items)
		if (item->type() < 20)
		{
			delete item;
			break;
		}
}