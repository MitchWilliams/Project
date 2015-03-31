#pragma once

#include "GameObjects.h"
#include "States.h"
#include "BasketballStats.h"
#include "GameControllers.h"
#include "MatchInfo.h"
#include <QGraphicsItem>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <cmath>


//#include "vector.h"

class StateContext;
class MatchInfo;
struct Region;
class Team;

enum attributes{
	closeShooting, midShooting, threePointShooting, passing, dribbling, rebounding, defending,
	blocking, stamina, athleticism, energy, ATTRIBUTES_MAX = energy
};

enum decisions{ shoot, pass, drive, DECISION_MAX = drive };

enum playerStates {
	off_court, idle_state, attacking_state, defending_state, off_ball_still, on_ball_still, moving_off_ball, moving_on_ball, 
	guarding_off_ball, guarding_on_ball, receiving_pass, driving,  PLAYER_STATES_MAX = driving
};

static Vector2D nullPos(-10, -10); //creates a global variable that is the equivalent of setting a screenPosition to NULL
								   //can't actually set to NULL as that just sets the co-ordinates to 0, 0

class Player : public MovingGameObject, public BasketballStats, public StateContext, public QGraphicsItem
{
private:
	vector<int> playerAttribs;
	string firstName;
	string surname;
	string position;
	float distFromBasket;
	int height;
	int id;
	int consecMakes;
	int consecMisses;
	int teamPlayingOn;
	Player* playerToGuard;
	MatchInfo* matchInfo;
	int onBallAction;
	char* imageFilePath;
	Region* defaultRegion;
	Team *teamOn;
	QGraphicsSimpleTextItem *label;
	int reboundingChance;
	

public:
	Player();

	void setInfo(string nFirstName, string nSurname, int nHeight, string nPosition, int nId);
	void setMatchInfo(MatchInfo* nInfo){ matchInfo = nInfo; }
	void setAttributes(vector<int> nAttribs);
	void setDistFromBasket(float nDistance){ distFromBasket = nDistance; }
	void setOnBallAction(int nAction){ onBallAction = nAction; }
	void setFilePath(char* nPath){ imageFilePath = nPath; }
	void setTeamPlayingOn(int nTeam){ teamPlayingOn = nTeam; }
	void setDefaultRegion(int nRegion, vector<Region*> regionsVec){ defaultRegion = regionsVec.at(nRegion); }
	void setPlayerToGuard(Player* nPlayer){ playerToGuard = nPlayer; }
	void setTeamPtr(Team* nTeam){ teamOn = nTeam; }
	void setStaticStateValues(bool runOnlyFrequentStates);
	void setReboundingChance(int nChance) { reboundingChance = nChance; }

	void update();
	void display();
	void move();
	
	float getDistFromBasket();
	float getDistFromBasket(Vector2D *evalPosition);
	float getFieldGoalPercentage();
	string getFirstName() { return firstName; }
	string getSurname() { return surname; }
	string getPosition(){ return position; }
	string getStatline(); //returns a string containing the players stats to be printed to screen
	int getHeight() { return height; }
	int getAttributes(int attribToGet);
	int getID(){ return id; }
	int getOnBallAction(){ return onBallAction; }
	int getTeamPlayingOn(){ return teamPlayingOn; }
	int getReboundingChance() {return reboundingChance;}
	MatchInfo* getMatchInfo(){ return matchInfo; }
	Player* getPlayerToGuard() { return playerToGuard; }
	Region* getDefaultRegion(){ return defaultRegion; }
	


	void clearAttributes(){ playerAttribs.clear(); }	
	int generateNumber(int max, int min);
	bool isInPossession();
	vector<Vector2D*> generatePositions(Region regionToGenerate);
	Vector2D generateSinglePosition(Region regionToGenerate);
	vector<int> evaluatePositions(vector<Vector2D*> positions);
	int evaluateCurrentPosition();
	float distToNearestTeammate();
	float distToNearestTeammate(Vector2D *evalPosition);
	void resetSpeed(){ speed = getAttributes(athleticism) / 20; }

	//graphics overloaded functions
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	QPainterPath shape() const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget) Q_DECL_OVERRIDE;

};

//Player States

class OffCourt : public State
{
public:

	OffCourt(StateContext* Context) : State(Context){};
	void execute(Player* player);
};


class Idle : public State
{
public:

	Idle(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class Attacking : public State
{
public:

	Attacking(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class Defending : public State
{
public:

	Defending(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class OffBallStill : public State
{
public:

	OffBallStill(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class OnBallStill : public State
{
public:

	OnBallStill(StateContext* Context) : State(Context){};
	void execute(Player* player);
	int makeDecision(Player* player);
};

class Moving
{
protected:
	bool isCloseToGoal(Player* player);
};

class MovingOffBall : public Moving, public State
{
public:

	MovingOffBall(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class MovingOnBall : public Moving, public State
{
public:

	MovingOnBall(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class Driving : public State
{
public:
	Driving(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class Guarding
{
protected:
	bool isOpponentCloserToBasket(Player* player);

};

class GuardingOffBall : public State, public Guarding
{
public:

	GuardingOffBall(StateContext* Context) : State(Context){};
	void execute(Player* player);
};

class GuardingOnBall : public State, public Guarding
{
public:

	GuardingOnBall(StateContext* Context) : State(Context){};
	void execute(Player* player);
	
};

class ReceivingPass : public State
{
public:

	ReceivingPass(StateContext* Context) : State(Context){};
	void execute(Player* player);
};
