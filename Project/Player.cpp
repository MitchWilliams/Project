#include "Player.h"

Player::Player()
{

	onBallAction = 4;

	//initialises all of the player states and adds them to the states vector
	availableStates.push_back(new OffCourt(this));
	availableStates.push_back(new Idle(this));
	availableStates.push_back(new Attacking(this));
	availableStates.push_back(new Defending(this));
	availableStates.push_back(new OffBallStill(this));
	availableStates.push_back(new OnBallStill(this));
	availableStates.push_back(new MovingOffBall(this));
	availableStates.push_back(new MovingOnBall(this));
	availableStates.push_back(new GuardingOffBall(this));
	availableStates.push_back(new GuardingOnBall(this));
	availableStates.push_back(new ReceivingPass(this));
	availableStates.push_back(new Driving(this));

	setPos(0, 0);

	label = new QGraphicsSimpleTextItem(this);

	float tempY = pos().y() + 40;
	label->setPos(this->pos().x(), tempY);

	

	//inPossession = false;
	srand(time(NULL));
	defaultRegion = new Region();
}

//populates attributes vector with values from database
void Player::setAttributes(vector<int> nAttribs)
{

	
	for (int i = 0; i < ATTRIBUTES_MAX; i++)
	{
		playerAttribs.push_back(nAttribs.at(i));
	}

	//sets starting energy to 100
	playerAttribs.push_back(99);
	resetSpeed();
}

//sets the textual information of players
void Player::setInfo(string nFirstName, string nSurname, int nHeight, string nPosition, int nId)
{
	firstName = nFirstName;
	surname = nSurname;
	height = nHeight;
	position = nPosition;
	id = nId;

	label->setText(QString::fromStdString(surname));
}

//returns the stats of the player at the current point in time
string Player::getStatline()
{
	string statline;
	string comma = " , ";

	statline = "Points:" + to_string(objectStats.at(points)) + comma + "Assists: " + to_string(objectStats.at(assists)) + comma
		+ "Rebounds: " + to_string(objectStats.at(rebounds)) + comma + "FG%: " + to_string(getFieldGoalPercentage());

	return statline;

}

//returns the requested attribute value
int Player::getAttributes(int attribToGet)
{
	return playerAttribs.at(attribToGet);
}

//updates the player
void Player::update()
{

	

	currentState->execute(this);
	QPointF newPosition = pos();
}


void Player::display()
{

}

void Player::move()
{
	
	//if goal position isn't null
	if (goalPosition != nullPos)
	{
		//get direction from current position to goal position
		Vector2D direction = goalPosition - screenPosition;
		float result = direction.Normalize();
		Vector2D newPosition;

		velocity.x = direction.x * speed;
		velocity.y = direction.y * speed;

		//move the player position towards the goal position
		newPosition = getScreenPosition() + velocity;

		setScreenPosition(newPosition);

	

		QPointF oldPosition = pos();
		setPos(mapToParent(-oldPosition));

		setPos(mapToParent(screenPosition.x, screenPosition.y));
	}
}

//returns the distance of the player from the basket being attacked
float Player::getDistFromBasket()
{
	
	float distance;
	Vector2D dist;
	
	if (matchInfo->getTeamInPossession()->getID() == 0)
	{
		distance = dist.Distance(screenPosition, matchInfo->getCourt()->getBasketPos("right"));
	}
	else if (matchInfo->getTeamInPossession()->getID() == 1)
	{
		distance = dist.Distance(screenPosition, matchInfo->getCourt()->getBasketPos("left"));
	}
	
	distance = distance / DISTANCE_ADJUSTMENT;



	return distance;
}

//gets the distance of a potential position from the basket
float Player::getDistFromBasket(Vector2D *evalPosition)
{

	float distance;
	Vector2D dist;

	if (teamPlayingOn == 1)
	{
		distance = dist.Distance(*evalPosition, matchInfo->getCourt()->getBasketPos("right"));
	}
	else if (teamPlayingOn == 2)
	{
		distance = dist.Distance(*evalPosition, matchInfo->getCourt()->getBasketPos("left"));
	}

	distance = distance / DISTANCE_ADJUSTMENT;



	return distance;
}

//generates a random number within the upper & lower bounds
int Player::generateNumber(int max, int min)
{
	

	int rnd;

	rnd = rand() % (max - min) + min;

	return rnd;
}


//calculates and returns a players field goal percentage
float Player::getFieldGoalPercentage()
{
	float fgp;
	int fga = objectStats.at(fieldGoalAttempts);
	int fgm = objectStats.at(fieldGoalMakes);



	if (fga > 0)
		fgp = (float)fgm / (float)fga * 100;
	else
		fgp = 0;

	return fgp;


}

//determines whether or not the player is currently in possession
bool Player::isInPossession()
{
	if (matchInfo->getPlayerInPossession() == NULL)
	{
		return false;
	}

	if (matchInfo->getPlayerInPossession()->getID() == id)
		return true;
	else
		return false;
}

QRectF Player::boundingRect() const
{
	qreal adjust = 0.5;

	return QRectF(0 - adjust, 0 - adjust, 22 + adjust, 22 + adjust);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	//painter->setBrush(color);
	painter->setBrush(QPixmap(imageFilePath));
	painter->drawRect(QRectF(0, 0, 22, 22));
}

QPainterPath Player::shape() const
{
	QPainterPath path;
	path.addRect(0, 0, 22, 22);

	return path;
}

//generates a list of potential positions to move to within a given regien
vector<Vector2D*> Player::generatePositions(Region regionToGenerate)
{
	vector<Vector2D*> positions;

	for (int i = 0; i < 20; i++)
	{
		Vector2D *tempVec = new Vector2D();

		tempVec->x = generateNumber(regionToGenerate.rightX, regionToGenerate.leftX);
		tempVec->y = generateNumber(regionToGenerate.bottomY, regionToGenerate.topY);

		positions.push_back(tempVec);
		
	}

	return positions;
}

//generates a single position within a given region
Vector2D Player::generateSinglePosition(Region regionToGenerate)
{
	Vector2D tempVec;

	tempVec.x = generateNumber((int)regionToGenerate.rightX, (int)regionToGenerate.leftX);
	tempVec.y = generateNumber((int)regionToGenerate.bottomY, (int)regionToGenerate.topY);

	return tempVec;
}

//evaluates the potential positions and assigns them a score 
vector<int> Player::evaluatePositions(vector<Vector2D*> positions)
{
	//criteria:
	//shooting ability from position
	//spacing from other teammates
	
	
	vector<int> posScores;
	int tempPosScore;

	for (int i = 0; i < positions.size(); i++)
	{
		tempPosScore = 0;

		if (getDistFromBasket(positions.at(i)) <= 12)
		{
			tempPosScore += getAttributes(closeShooting);
		}
		else if (getDistFromBasket(positions.at(i)) > 12 && getDistFromBasket(positions.at(i)) <= 20)
		{
			tempPosScore += getAttributes(midShooting);
		}
		else if (getDistFromBasket(positions.at(i)) > 20)
		{
			tempPosScore += getAttributes(threePointShooting);
		}

		tempPosScore += distToNearestTeammate(positions.at(i));

		posScores.push_back(tempPosScore);
	}

	return posScores;
}

//evaluates current position and assigns it a score
int Player::evaluateCurrentPosition()
{
	//criteria:
	//shooting ability from position
	//spacing from other teammates
	//dist from defender at current position

	int posScore = 0;

	if (getDistFromBasket() <= 12)
	{
		posScore += getAttributes(closeShooting);
	}
	else if (getDistFromBasket() > 12 && getDistFromBasket() <= 20)
	{
		posScore += getAttributes(midShooting);
	}
	else if (getDistFromBasket() > 20)
	{
		posScore += getAttributes(threePointShooting);
	}

	posScore += matchInfo->getDistBetweenPlayers(this, playerToGuard);

	posScore += distToNearestTeammate(); //higher the better

	return posScore;
}

//gets the distance from current position to the nearest teammate
float Player::distToNearestTeammate()
{
	float distance = 0;

	for (int i = 0; i < 5; i++)
	{
		Player* tempPlayer = teamOn->getPlayer(i);

		if (tempPlayer->getID() != id) //prevents player from comparing against itself
		{
			if (distance == 0)
				distance = matchInfo->getDistBetweenPlayers(this, tempPlayer);
			else
			{	
				//if distance is lower than current lowest, change it
				if (matchInfo->getDistBetweenPlayers(this, tempPlayer) < distance)
					distance = matchInfo->getDistBetweenPlayers(this, tempPlayer);
			}
		}
	}

	return distance;
}

//gets the distance to the nearest teammate from a given position
float Player::distToNearestTeammate(Vector2D *evalPosition)
{
	float distance = 0;

	for (int i = 0; i < 5; i++)
	{
		Player* tempPlayer = teamOn->getPlayer(i);

		if (tempPlayer->getID() != id) //prevents player from comparing against itself
		{
			if (distance == 0)
				distance = matchInfo->getDistBetweenPoints(*evalPosition, tempPlayer->getScreenPosition());
			else
			{
				if (matchInfo->getDistBetweenPoints(*evalPosition, tempPlayer->getScreenPosition()) < distance)
					distance = matchInfo->getDistBetweenPoints(*evalPosition, tempPlayer->getScreenPosition());
			}
		}
	}

	return distance;

}

//sets whether or not only the frequent states should be run
void Player::setStaticStateValues(bool runOnlyFrequentStates)
{
	currentState->setFrequentStates(runOnlyFrequentStates);
}

void OffCourt::execute(Player* player)
{
	//do nothing

}

void Idle::execute(Player* player)
{
	//wait until game starts
	//if team is in possession go to attacking

	//if team is not in possession go to defending
}

void Attacking::execute(Player* player)
{
	//if have ball move to on ball still

	if (player->isInPossession() == true)
	{	
		//if player is good at dribbling, bring the ball up court, else pass it
		if (player->getAttributes(dribbling) < 75)
			player->setState(on_ball_still);
		else
			player->setState(moving_on_ball);
	}
	else
	{
		//else go to off ball still
		player->setState(moving_off_ball);
	}

	//set the goal position to be a random position within the default region
	player->setGoalPosition(player->generateSinglePosition(*player->getDefaultRegion()));
	player->update();
	
}

void Defending::execute(Player* player)
{
	//get defensive assignment
	//if opponent has ball go to guarding on ball
	//else go to guarding off ball

	if (player->getMatchInfo()->getPlayerInPossession()->getID() == player->getPlayerToGuard()->getID())
	{
		player->setState(guarding_on_ball);
	}
	else
	{
		player->setState(guarding_off_ball);
	}

}

void OffBallStill::execute(Player* player)
{
	//get score for current position
	//generate potential positions
	//evaluate potential positions
	//if current position score is above average of potential positions
	//stay still else
	//choose best one and set as target
	//go to moving off ball

	player->resetSpeed();

	if (runOnlyFrequentStates == false)
	{
		

		int currentPositionScore;
		vector<int> potentialPositionScores;
		vector <Vector2D*> potentialPositions;
		int currentScoreHigherCount = 0;
		int currentScoreLowerCount = 0;
		int bestPotentialScore = 0;
		int bestPotentialScorePos;
		Region potentialRegion;

		if (player->isInPossession() == true)
		{
			player->setState(on_ball_still);
			player->update();
		}

		//set the half of the court in which to generate potential positions
		if (player->getTeamPlayingOn() == 1)
		{
			potentialRegion.leftX = 382;
			potentialRegion.rightX = 535;
			potentialRegion.bottomY = 312;
			potentialRegion.topY = 31;
		}
		else
		{
			potentialRegion.leftX = 53;
			potentialRegion.rightX = 205;
			potentialRegion.bottomY = 312;
			potentialRegion.topY = 31;
		}

		currentPositionScore = player->evaluateCurrentPosition();
		potentialPositions = player->generatePositions(potentialRegion);
		potentialPositionScores = player->evaluatePositions(potentialPositions);

		//iterate through list of position scores and count the number of positions better and worse than current position
		for (int i = 0; i < potentialPositionScores.size(); i++)
		{
			if (currentPositionScore > potentialPositionScores.at(i))
				currentScoreHigherCount++;
			else
				currentScoreLowerCount++;

			//keep track of the best potential position
			if (potentialPositionScores.at(i) > bestPotentialScore)
			{
				bestPotentialScore = potentialPositionScores.at(i);
				bestPotentialScorePos = i;
			}

		}

		//if there are more potential positions better than the current one than there are worse
		//set goal position to the best potential position
		if (currentScoreLowerCount > currentScoreHigherCount)
		{
			player->setGoalPosition(*potentialPositions.at(bestPotentialScorePos));
			player->setState(moving_off_ball);
		}
		else
		{
			player->setGoalPosition(nullPos);
		}
	}

	

}

void OnBallStill::execute(Player* player)
{
	
	
	if (runOnlyFrequentStates == false)
	{

		player->setGoalPosition(nullPos);

		if (player->isInPossession() == true)
		{
			//if player is in this state in their own half it is because their dribbling
			//attribute is low so tell them to pass the ball, else call the make decision function
			if (player->getTeamPlayingOn() == 1)
			{
				if (player->getScreenPosition().x < 336)
				{
					player->setOnBallAction(pass);
				}
				else
				{
					player->setOnBallAction(makeDecision(player));
				}
			}

			if (player->getTeamPlayingOn() == 2)
			{
				if (player->getScreenPosition().x > 256)
				{
					player->setOnBallAction(pass);
				}
				else
				{
					player->setOnBallAction(makeDecision(player));
				}
			}

		}
		else
		{
			player->setState(off_ball_still);
			player->setOnBallAction(4);
			player->update();
		}
	}
	

	
}

//determines what the player should do with the ball
int OnBallStill::makeDecision(Player* player)
{
	int randNum;
	int returnVal = 4;
	int shootingArea;
	int shootingChance = 50;
	int drivingChance = 50;
	int passingChance = 50;

	string shootingSkill;
	string drivingSkill;
	string passingSkill;

	string defenderNear;
	string shotClockLow;
	string distFromBasket;

	string sqlCommandString;
	char* sqlCommand;
	char* sqlCommand2;
	string reccomendationOne;
	string reccomendationTwo;

	RuleDatabaseHandler rdbh;

	//sets the values of all the variables needed for the query
	int shotClockRemaining = player->getMatchInfo()->getshotClockRemaining();

	float distFromDefender = player->getMatchInfo()->getDistBetweenPlayers(player, player->getPlayerToGuard());

	
	if (distFromDefender <= 4)
	{
		defenderNear = "'Close'";
	}
	else if (distFromDefender > 4 && distFromDefender <= 10)
	{
		defenderNear = "'Medium'";
	}
	else if (distFromDefender > 10)
	{
		defenderNear = "'Far'";
	}

	if (shotClockRemaining <= 6)
	{
		shotClockLow = "'Low'";
	}
	else if (shotClockRemaining > 6 && shotClockRemaining <= 16)
	{
		shotClockLow = "'Medium'";
	}
	else if (shotClockRemaining > 16)
	{
		shotClockLow = "'High'";
	}


	if (player->getDistFromBasket() <= 12)
	{
		distFromBasket = "'Close'";
		shootingArea = closeShooting;
	}
	else if (player->getDistFromBasket() > 12 && player->getDistFromBasket() <= 20)
	{
		distFromBasket = "'Medium'";
		shootingArea = midShooting;
	}
	else if (player->getDistFromBasket() > 20)
	{
		distFromBasket = "'Far'";
		shootingArea = threePointShooting;
	}

	if (player->getAttributes(shootingArea) <= 50)
	{
		shootingSkill = "'Low'";
	}
	else if (player->getAttributes(shootingArea) > 50 && player->getAttributes(shootingArea) <= 75)
	{
		shootingSkill = "'Medium'";
	}
	else if (player->getAttributes(shootingArea) > 75)
	{
		shootingSkill = "'High'";
	}

	if (player->getAttributes(passing) <= 50)
	{
		passingSkill = "'Low'";
	}
	else if (player->getAttributes(passing) > 50 && player->getAttributes(passing) <= 75)
	{
		passingSkill = "'Medium'";
	}
	else if (player->getAttributes(passing) > 75)
	{
		passingSkill = "'High'";
	}

	if (player->getAttributes(dribbling) <= 50)
	{
		drivingSkill = "'Low'";
	}
	else if (player->getAttributes(dribbling) > 50 && player->getAttributes(dribbling) <= 75)
	{
		drivingSkill = "'Medium'";
	}
	else if (player->getAttributes(dribbling) > 75)
	{
		drivingSkill = "'High'";
	}

	//creates the query for the first database
	sqlCommandString = "SELECT RECCOMENDATION FROM NONSKILLRULES WHERE DEFENDERNEAR = " + defenderNear + " AND DISTFROMBASKET = " +
		distFromBasket + " AND SHOTCLOCKLOW = " + shotClockLow;

	sqlCommand = new char[sqlCommandString.size() + 1];
	memcpy(sqlCommand, sqlCommandString.c_str(), sqlCommandString.size() + 1);
	reccomendationOne = rdbh.getReccomendation(sqlCommand);
	delete sqlCommand;

	//creates the query for the first database
	sqlCommandString = "SELECT RECCOMENDATION FROM SKILLRULES WHERE SHOOTINGSKILL = " + shootingSkill + " AND DRIVINGSKILL = " +
		drivingSkill + " AND PASSINGSKILL = " + passingSkill;

	sqlCommand2 = new char[sqlCommandString.size() + 1];
	memcpy(sqlCommand2, sqlCommandString.c_str(), sqlCommandString.size() + 1);
	reccomendationTwo = rdbh.getReccomendation(sqlCommand2);
	delete sqlCommand2;

	//if both rule databases give the same reccomendation, perform that action
	if (reccomendationOne == reccomendationTwo)
	{
		if (reccomendationOne == "Shoot")
			returnVal = shoot;
		else if (reccomendationOne == "Pass")
			returnVal = pass;
		else
			returnVal = drive;
	}
	else
	{	//if not, make it more likely that one of the reccomended actions are performed
		if (reccomendationOne == "Shoot")
			shootingChance += 50;
		else if (reccomendationOne == "Pass")
			passingChance += 50;
		else
			drivingChance += 50;

		if (reccomendationTwo == "Shoot")
			shootingChance += 50;
		else if (reccomendationTwo == "Pass")
			passingChance += 50;
		else
			drivingChance += 50;

		randNum = player->generateNumber((shootingChance + drivingChance + passingChance), 1);

		if (randNum <= shootingChance)
			returnVal = shoot;
		else if (randNum > shootingChance && randNum <= (shootingChance + drivingChance))
			returnVal = drive;
		else
			returnVal = pass;

	}

	return returnVal;

}

void MovingOnBall::execute(Player* player)
{
	player->setOnBallAction(4);
	player->setSpeed(player->getAttributes(athleticism) / 25);

	if (runOnlyFrequentStates == true)
	{
		//stops the player if they are close to their goal position
		if (isCloseToGoal(player) == true)
		{
			player->setState(on_ball_still);
		}
	}

}

void Driving::execute(Player* player)
{
	//move towards basket
	player->resetSpeed();
	if (player->getTeamPlayingOn() == 1)
		player->setGoalPosition(player->getMatchInfo()->getCourt()->getBasketPos("right"));
	else
		player->setGoalPosition(player->getMatchInfo()->getCourt()->getBasketPos("left"));



	player->setState(on_ball_still);
	player->setOnBallAction(4);
}

void MovingOffBall::execute(Player* player)
{
	player->resetSpeed();
	
	//if target position reached go to off ball still
	if (runOnlyFrequentStates == true)
	{
		if (isCloseToGoal(player) == true)
		{
			player->setState(off_ball_still);
		}
		else
		{

		}
	}


}

//checks if the player is near their goal position
bool Moving::isCloseToGoal(Player* player)
{
	Vector2D currentPos = player->getScreenPosition();
	Vector2D goalPos = player->getGoalPosition();
	bool isClose = false;

	if (player->getMatchInfo()->getDistBetweenPoints(currentPos, goalPos) < player->getAttributes(athleticism)/20)
		isClose = true;


	return isClose;
	
}

void GuardingOnBall::execute(Player* player)
{
	//always attempt to keep self between basket and player on ball
	//if player has gone past then chase
	player->resetSpeed();
	if (runOnlyFrequentStates == true)
	{
		if (isOpponentCloserToBasket(player) == true)
		{
			if (player->getTeamPlayingOn() == 1)
				player->setGoalPosition(player->getMatchInfo()->getCourt()->getBasketPos("left"));
				
			else
				player->setGoalPosition(player->getMatchInfo()->getCourt()->getBasketPos("right"));
				
		}
		else
		{
			float distFromOpponent = player->getMatchInfo()->getDistBetweenPlayers(player, player->getPlayerToGuard());

			if (distFromOpponent > 6)
			{
				player->setGoalPosition(player->getPlayerToGuard()->getScreenPosition());
			}
			else
			{
				player->setGoalPosition(nullPos);
			}
		}

	}
	


}

//determines if opposing player is nearer to the basket than the player
bool Guarding::isOpponentCloserToBasket(Player* player)
{
	bool opponentCloser = false;
	
	if (player->getTeamPlayingOn() == 1)
	{
		if (player->getScreenPosition().x > player->getPlayerToGuard()->getScreenPosition().x)
			opponentCloser = true;
	}
	else
	{
		if (player->getScreenPosition().x < player->getPlayerToGuard()->getScreenPosition().x)
			opponentCloser = true;
	}

	float s = player->getDistFromBasket();

	if (s < 6)
		opponentCloser = false;

	//float q = player->getPlayerToGuard()->getDistFromBasket();

	return opponentCloser;

}

void GuardingOffBall::execute(Player* player)
{
	//get x distance from opponent depending on behaviour
	player->resetSpeed();

	if (runOnlyFrequentStates == true)
	{
		if (isOpponentCloserToBasket(player) == true)
		{
			if (player->getTeamPlayingOn() == 1)
				player->setGoalPosition(player->getMatchInfo()->getCourt()->getBasketPos("left"));
				//player->setGoalPosition(Vector2D(player->getPlayerToGuard()->getScreenPosition().x - 20, player->getPlayerToGuard()->getScreenPosition().y));
			else
				player->setGoalPosition(player->getMatchInfo()->getCourt()->getBasketPos("right"));
				//player->setGoalPosition (Vector2D(player->getPlayerToGuard()->getScreenPosition().x + 20, player->getPlayerToGuard()->getScreenPosition().y));
		}
		else
		{
			float distFromOpponent = player->getMatchInfo()->getDistBetweenPlayers(player, player->getPlayerToGuard());

			if (distFromOpponent > 6)
			{
				player->setGoalPosition(player->getPlayerToGuard()->getScreenPosition());
				//player->move();
			}
			else
			{
				player->setGoalPosition(nullPos);
			}
		}

	}


}

void ReceivingPass::execute(Player* player)
{
	//stay in current position
	player->setGoalPosition(nullPos);
	player->resetSpeed();

	//if in possession go to on ball still
	if (player->isInPossession() == true)
	{
		player->setState(on_ball_still);
	}


}