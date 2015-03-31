#include "GameObjects.h"

Court::Court()
{
	//setup the court dimensions and the positions of the baskets
	width = 590;
	length = 342;
	leftBasketPos.x = 64;
	leftBasketPos.y = 170;
	rightBasketPos.x = 528;
	rightBasketPos.y = 170;

	setPos(mapToParent(0, 0));

}

QRectF Court::boundingRect() const
{
	qreal adjust = 0.5;

	return QRectF(0 - adjust, 0 - adjust, 590 + adjust, 342 + adjust);
}

void Court::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	//painter->setBrush(color);
	painter->setBrush(QPixmap("court.jpg"));
	painter->drawRect(QRectF(0, 0, 590, 342));
}

QPainterPath Court::shape() const
{
	QPainterPath path;
	path.addRect(0, 0, 590, 342);

	return path;
}

Vector2D Court::getBasketPos(string side)
{
	if (side == "left")
		return leftBasketPos;
	else if (side == "right")
		return rightBasketPos;

}

