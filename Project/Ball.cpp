#include "Ball.h"

Ball::Ball()
{
	setPos(mapToParent(0, 0));

}

//Sets the balls bounding rectangle
QRectF Ball::boundingRect() const
{
	qreal adjust = 0.5;

	return QRectF(0 - adjust, 0 - adjust, 11 + adjust, 11 + adjust);
}

//sets the texture and shape to draw the ball
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	//painter->setBrush(color);
	painter->setBrush(QPixmap("ball.jpg"));
	painter->drawEllipse(0, 0, 11, 11);
}


QPainterPath Ball::shape() const
{
	QPainterPath path;
	path.addRect(0, 0, 11, 11);

	return path;
}

//updates the position of the ball
void Ball::update()
{
	QPointF oldPosition = pos();
	setPos(mapToParent(-oldPosition));

	//sets screen position to the player in possession of it
	screenPosition = owner->getScreenPosition();

	setPos(mapToParent(screenPosition.x, screenPosition.y));
	QPointF newPosition = pos();
}