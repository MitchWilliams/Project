#pragma once

//#include "Player.h"
#include "Team.h"

class Player;
class BasketballStats;
class Team;
class Court;
class Ball;

enum regions{left_PG, left_SG, left_SF, left_PF, left_C, right_PG, right_SG, right_SF, right_PF, right_C};
const float DISTANCE_ADJUSTMENT = 6.28; //divide distance by this to convert from pixel distance to foot

//defines an area of the court
struct Region
{
	float leftX, rightX, topY, bottomY;

};

class MatchInfo
{
protected:
	static Player *playerInPossession;
	static Player *previousPlayerInPossession;
	static Team *teamInPossession;
	static int minutesRemaining;
	static int secondsRemaining;
	static int shotClockRemaining;
	static int quarter;
	static Court *court;
	static Ball *ball;
	static Team* teamOnePtr;
	static Team* teamTwoPtr;
	//static Ball ball;
public:
	int getMinutesRemaining(){ return minutesRemaining; }
	int getSecondsRemaining(){ return secondsRemaining; }
	int getshotClockRemaining(){ return shotClockRemaining; }
	int getQuarter(){ return quarter; }
	Team* getTeamInPossession(){ return teamInPossession; }
	Player* getPlayerInPossession(){ return playerInPossession; }
	Player* getPreviousPlayerInPossession(){ return previousPlayerInPossession; }
	Court* getCourt(){return court;}
	float getDistBetweenPlayers(Player* playerOne, Player* playerTwo);
	float getDistBetweenPoints(Vector2D pointOne, Vector2D pointTwo);
	Team* getTeamOnePtr(){ return teamOnePtr; }
	Team* getTeamTwoPtr(){ return teamTwoPtr; }
	vector<Region*> courtRegions;
	void createRegion(float nLeft, float nRight, float nTop, float nBottom);
	void setupRegions();
};

