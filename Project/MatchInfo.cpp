#include "MatchInfo.h"

//sets the initial values of the static variables
int MatchInfo::minutesRemaining = 12;
int MatchInfo::secondsRemaining = 0;
int MatchInfo::quarter = 1;
int MatchInfo::shotClockRemaining = 24;
Player* MatchInfo::previousPlayerInPossession = NULL;
Player* MatchInfo::playerInPossession = NULL;
Team* MatchInfo::teamInPossession = NULL;
Court* MatchInfo::court = NULL;
Team* MatchInfo::teamOnePtr = NULL;
Team* MatchInfo::teamTwoPtr = NULL;
Ball* MatchInfo::ball = NULL;

//returns the distance between two players
float MatchInfo::getDistBetweenPlayers(Player* playerOne, Player* playerTwo)
{
	

	Vector2D dist;
	
	//gets the distance in terms of pixels
	float distance = dist.Distance(playerOne->getScreenPosition(), playerTwo->getScreenPosition());

	//divides it by the adjustment const so as to get the value in feet, which is used for certain calculations
	distance = distance / DISTANCE_ADJUSTMENT;

	return distance;
}

//returns the distance between two points on screen
float MatchInfo::getDistBetweenPoints(Vector2D pointOne, Vector2D pointTwo)
{

	Vector2D dist;

	float distance = dist.Distance(pointOne, pointTwo);

	distance = distance / DISTANCE_ADJUSTMENT;

	return distance;
}

//sets up the default regions for each position
void MatchInfo::setupRegions()
{
	//leftPGRegion
	createRegion(188, 233, 72, 271);

	//leftSGRegion
	createRegion(40, 206, 19, 113);

	//leftSFRegion
	createRegion(40, 206, 229, 325);

	//leftPFRegion
	createRegion(78, 150, 69, 271);

	//leftCRegion
	createRegion(75, 156, 114, 229);

	//rightPGRegion
	createRegion(356, 401, 72, 271);

	//rightSGRegion
	createRegion(382, 547, 19, 113);

	//rightSFRegion
	createRegion(382, 547, 229, 325);

	//rightPFRegion
	createRegion(441, 514, 69, 271);

	//rightCRegion
	createRegion(431, 520, 114, 229);
}

//creates a new court region given the required parameters
void MatchInfo::createRegion(float nLeft, float nRight, float nTop, float nBottom)
{
	Region *tempRegion = new Region;

	tempRegion->leftX = nLeft;
	tempRegion->rightX = nRight;
	tempRegion->topY = nTop;
	tempRegion->bottomY = nBottom;

	courtRegions.push_back(tempRegion);
}