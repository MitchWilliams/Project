#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "GameControllers.h"
//#include "States.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "vector2D.h"
#include <QGraphicsItem>
#include <qpainter.h>

using namespace std;



class Player;


class GameObject
{
protected:
	Vector2D screenPosition;
	int objectID;
public:
	
	Vector2D getScreenPosition(){ return screenPosition; }
	void setScreenPosition(Vector2D nPosition){ screenPosition = nPosition; }
};

class MovingGameObject : public GameObject
{
protected:
	float direction;
	int speed;
	Vector2D velocity;
	Vector2D origin;
	int mass;
	Vector2D goalPosition;
public:

	Vector2D getGoalPosition(){ return goalPosition; }
	void setGoalPosition(Vector2D nGoalPosition){ goalPosition = nGoalPosition; }
	Vector2D getVelocity(){ return velocity; }
	Vector2D getOrigin(){ return origin; }
	float getDirection(){return direction;}
	int getSpeed(){ return speed;}
	void setSpeed(int nSpeed){ speed = nSpeed; }
	int getMass(){ return mass; }
};





class Court : public GameObject, public QGraphicsItem
{
private:
	Vector2D leftBasketPos;
	Vector2D rightBasketPos;

	int width;
	int length;
public:
	Court();

	void display();
	void update();
	int getWidth(){ return width; }
	int getLength(){ return length; }
	Vector2D getBasketPos(string side);

	//graphics overloaded functions
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	QPainterPath shape() const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget) Q_DECL_OVERRIDE;
};



