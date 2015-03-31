#pragma once

#include "Player.h"

using namespace std;

class Ball : public MovingGameObject, public QGraphicsItem
{
private:
	Player* owner;
public:
	Ball();

	void move(int courtWidth, int courtLength);
	void update();
	void display();
	void setOwner(Player* nOwner){ owner = nOwner; }

	//graphics overloaded functions
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	QPainterPath shape() const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget) Q_DECL_OVERRIDE;
};