#include "matchscreen.h"
#include <qtimer.h>


MatchScreen::MatchScreen(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	gamePaused = true;
	currentPlayOver = false;
	firstTimePlayClicked = true;
	gameTimer = new QTimer(this);
	renderTimer = new QTimer(this);
	scene = new QGraphicsScene();
	painter = new QPainter();
	court = new Court();
	ball = new Ball();
	//seeds the random number function with the time
	srand(time(NULL));
	MatchScreen::gameView->setAlignment(Qt::AlignLeft);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(0, 0, 590, 342);

	scene->addItem(court);
	
	gameOver = false;
	//populate regions
	setupRegions();


}


MatchScreen::~MatchScreen()
{
	
}

//creates the two team objects for the match and populates them with players
void MatchScreen::createTeams(vector <Player*> nTeamOne, vector <Player*> nTeamTwo)
{
	//create the teams
	Team playerTeam(nTeamOne, false, 0, this);
	Team aiTeam(nTeamTwo, true, 1, this);

	//add teams to team vector
	teams.push_back(playerTeam);
	teams.push_back(aiTeam);

	//sets the pointers in MatchInfo
	teamOnePtr = &teams.at(teamOne);
	teamTwoPtr = &teams.at(teamTwo);

	//gives the players on each team a pointer to the team they are on
	for (int i = 0; i < 5; i++)
	{
		teams.at(teamOne).getPlayer(i)->setTeamPtr(&teams.at(teamOne));
		teams.at(teamTwo).getPlayer(i)->setTeamPtr(&teams.at(teamTwo));
	}
}

//generates a random number within the upper & lower bounds
int MatchScreen::generateNumber(int max, int min)
{


	int rnd;

	rnd = rand() % (max - min) + min;

	return rnd;
}

//Triggered every time the play/pause button is clicked
void MatchScreen::on_playButton_clicked()
{
	//runs initial match setup code first time the button is pressed
	if (firstTimePlayClicked == true)
	{
		
		
		runTipOff();
		updatePositionLabels();


		resetPlayerPosition();
		teams.at(teamOne).resetPlayerStats();
		teams.at(teamTwo).resetPlayerStats();
		teams.at(teamOne).setStartStates();
		teams.at(teamTwo).setStartStates();
		//set player default regions
		teams.at(teamOne).setPlayerDefaultRegions(this);
		teams.at(teamTwo).setPlayerDefaultRegions(this);

		setDefensiveAssignments();

		//adds the players and the ball to the scene so they can be shown on screen
		for (int i = 0; i < 5; i++)
		{
			scene->addItem(teams.at(teamOne).getPlayer(i));
			scene->addItem(teams.at(teamTwo).getPlayer(i));
		}
		scene->addItem(ball);

		firstTimePlayClicked = false;
	}

	if (gamePaused == false)
	{
		//if the game is currently being played

		//change the text of the button
		MatchScreen::playButton->setText(QString::fromStdString("Play"));

		//pause the game
		gameTimer->stop();
		renderTimer->stop();
		gamePaused = true;
	}
	else
	{
		//if the game is currently paused

		//change the text of the button
		MatchScreen::playButton->setText(QString::fromStdString("Pause"));

		//start/resume the timers
		gameTimer->start(1000);
		renderTimer->start(1000/33);

		//trigger the specified functions every time the timers run out
		connect(gameTimer, SIGNAL(timeout()), this, SLOT(updateMatch()));
		connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderMatch()));
		gamePaused = false;
	}
	
	

	
	
	
}

//updates the match - called once every second
void MatchScreen::updateMatch()
{
	

	//checks if the game has finished
	if (gameOver == false)
	{
		//decrements the minutes and resets the seconds to 60
		if (secondsRemaining <= 0)
		{
			minutesRemaining--;
			
			if (minutesRemaining >= 0)
				secondsRemaining = 60;
		}

		//loop may seem unneccessary but is in place so that it can be broken out of under certain conditions
		for (int i = 0; i < 1; i++)
		{

			//if the quarter is over
			if (minutesRemaining <= 0 && secondsRemaining <= 0)
			{
				//go to next quarter if match not over
				if (quarter < 4)
					goToNextQuarter();
				else
				{
					//else end the match
					updatePlayerStats();
					gameOver = true;
					break;
				}

			}

			//call the function that processes the match actions
			runMatch();

			//decrement the in game clocks
			shotClockRemaining -= 3;
			secondsRemaining -= 3;

			if (secondsRemaining <= 0 && minutesRemaining > 0)
			{
				minutesRemaining--;
				secondsRemaining = 60;
			}
			
			//change the possession if necessary
			if (currentPlayOver == true)
			{
				changeTeamPossession();
				break;
			}

		}

		//change the possession if the shot clock expires
		if (shotClockRemaining <= 0)
		{
			changeTeamPossession();
		}

		writeGameTime();
		
	}
	else if (gameOver == true)
	{
		//end the match

		MatchScreen::matchText->append(QString::fromStdString("Play simulation over"));

		writeMatchText(getScore());
		gameTimer->stop();
		renderTimer->stop();
	}

}

//runs the match actions
void MatchScreen::runMatch()
{
	int decision;

	//updates the players
	//the false flag tells the update function that this is only called once a second
	//rather than 30 times a second
	teams.at(teamOne).updatePlayers(false);
	teams.at(teamTwo).updatePlayers(false);
	
	//get the decision of what the player in possession is going to do with the ball
	decision = playerInPossession->getOnBallAction();

	//call the relevant sim function depending on if they decide to shoot, pass or drive
	switch (decision)
	{
	case shoot:
		simShot();
		break;
	case pass:
		simPass();
		break;
	case drive:
		simDrive();
		break;
	default:
		break;
	}


	
}

//simulate the result of a shot
void MatchScreen::simShot()
{
	string output;
	int chanceOfSuccess, randNum;


	//Print that a shot has been attempted
	output = "Shot attempted by " + playerInPossession->getFirstName() + " " + playerInPossession->getSurname();
	MatchScreen::matchText->append(QString::fromStdString(output));

	//increase the three point attempts if in three point range
	if (playerInPossession->getDistFromBasket() > 22)
	{
		playerInPossession->increaseStats(threePointAttempts, 1);
		teamInPossession->increaseStats(threePointAttempts, 1);
	}

	//get the percentage chance of the shot being successful
	chanceOfSuccess = getShotChance();

	//increase field goal attempts stat
	teamInPossession->increaseStats(fieldGoalAttempts, 1);
	playerInPossession->increaseStats(fieldGoalAttempts, 1);
	randNum = generateNumber(100, 1);

	//determine if the shot is successful or not
	if (randNum > chanceOfSuccess)
	{
		unsuccessfulShot();
	}
	else
	{
		successfulShot();
	}
	

	
}

//simulates the result of a pass
void MatchScreen::simPass()
{
	string output;
	int chanceOfSuccess, randNum, randNum2;
	Player *playerToPassTo;

	//print that a pass has been attempted
	output = "Pass attempted by " + playerInPossession->getFirstName() + " " + playerInPossession->getSurname();
	MatchScreen::matchText->append(QString::fromStdString(output));

	//select the player to pass the ball to
	randNum2 = generateNumber(5, 1) - 1;
	playerToPassTo = teamInPossession->getPlayer(randNum2);

	//check that player selected isn't player in possession
	if (playerToPassTo->getID() == playerInPossession->getID())
	{
		if (randNum2 > 0)
			randNum2 -= 1;
		else
			randNum2 = 4;

		playerToPassTo = teamInPossession->getPlayer(randNum2);

	}

	//update state of player to pass to so that they don't move
	playerToPassTo->setState(receiving_pass);

	//get chance of pass being successful
	chanceOfSuccess = getPassChance(playerToPassTo);

	randNum = generateNumber(100, 1);

	//determine success of pass
	if (randNum > chanceOfSuccess)
	{
		output = "Pass unsuccessful";
		MatchScreen::matchText->append(QString::fromStdString(output));

		//if unsuccessful then end the current possession
		playerInPossession->increaseStats(turnovers, 1);
		playerInPossession = NULL;
		currentPlayOver = true;
		playerToPassTo->setState(off_ball_still);
	}
	else
	{

		output = "Pass successful";
		MatchScreen::matchText->append(QString::fromStdString(output));

		output = playerToPassTo->getFirstName() + " " + playerToPassTo->getSurname() + " now in possession";
		MatchScreen::matchText->append(QString::fromStdString(output));

		//if pass is successful then change the player in possession
		previousPlayerInPossession = playerInPossession;
		playerInPossession = playerToPassTo;


	}

	
}

//writes text to the match text textbox
void MatchScreen::writeMatchText(string output)
{
	MatchScreen::matchText->append(QString::fromStdString(output));
}

//simulates the result of a drive
void MatchScreen::simDrive()
{
	string output;
	int chanceOfSuccess, randNum;


	output = "Drive attempted by " + playerInPossession->getFirstName() + " " + playerInPossession->getSurname();
	writeMatchText(output);

	//gets the chance of success
	chanceOfSuccess = getDriveChance();

	randNum = generateNumber(100, 1);

	if (randNum > chanceOfSuccess)
	{
		output = "Drive unsuccessful";
	}
	else
	{
		//change player state if drive successful
		output = "Drive successful";
		playerInPossession->setState(driving);
	}

	MatchScreen::matchText->append(QString::fromStdString(output));

}

//processes the results of a successful shot
void MatchScreen::successfulShot()
{
	string output = "Shot successful";

	//increase stats for points, field goal makes etc
	if (playerInPossession->getDistFromBasket() > 21)
	{
		playerInPossession->increaseStats(points, 3);
		playerInPossession->increaseStats(threePointMakes, 1);
		playerInPossession->increaseStats(fieldGoalMakes, 1);

		teamInPossession->increaseStats(fieldGoalMakes, 1);
		teamInPossession->increaseStats(points, 3);
		teamInPossession->increaseStats(threePointMakes, 1);
	}
	else
	{
		playerInPossession->increaseStats(points, 2);
		playerInPossession->increaseStats(fieldGoalMakes, 1);
		teamInPossession->increaseStats(points, 2);
		teamInPossession->increaseStats(fieldGoalMakes, 1);
	}

	writeMatchText(output);

	//increase the assist total for the player that setup the shot (if there was one)
	if (previousPlayerInPossession)
	{
		previousPlayerInPossession->increaseStats(assists, 1);
		output = "Assist by " + previousPlayerInPossession->getFirstName() + " " + previousPlayerInPossession->getSurname();
		writeMatchText(output);
	}

	currentPlayOver = true;
	playerInPossession = NULL;
}

//returns the current score and updates the score labels
string MatchScreen::getScore()
{
	string output;

	output = "Team One: " + to_string(teams.at(teamOne).getStats(points)) + " Team Two: " + to_string(teams.at(teamTwo).getStats(points));
	
	int teamOneScore = teams.at(teamOne).getStats(points);
	int teamTwoScore = teams.at(teamTwo).getStats(points);

	MatchScreen::teamOneScoreLabel->setText(QString::number(teamOneScore));
	MatchScreen::teamTwoScoreLabel->setText(QString::number(teamTwoScore));

	return output; 
}

//processes the change of possession
void MatchScreen::changeTeamPossession()
{
	if (teamInPossession->getID() == teams.at(teamOne).getID())
	{
		teamInPossession = &teams.at(teamTwo);
		writeMatchText("Team Two now in possession");
	}
	else
	{
		teamInPossession = &teams.at(teamOne);
		writeMatchText("Team One now in possession");
	}
	
	//if there is no player in possession, give the ball to the teams point guard
	if (playerInPossession == NULL)
		playerInPossession = teamInPossession->getPointGuard();
	previousPlayerInPossession = NULL;
	writeLineBreak();
	writeGameTime();
	writeMatchText(getScore());
	writeLineBreak();
	resetShotClock();
	currentPlayOver = false;

	//set the appropriate player states
	teams.at(teamOne).setStartStates();
	teams.at(teamTwo).setStartStates();
	updatePlayerStats();
}

//writes a line break to the match text box
void MatchScreen::writeLineBreak()
{
	string lineBreak = "________________________________________________________";
	writeMatchText(lineBreak);
}

//resets players to their start positions
void MatchScreen::resetPlayerPosition()
{
	for (int i = 0; i < teams.size(); i++)
	{
		teams.at(i).setStartPositions();
	}
}

//writes the game time to the screen
void MatchScreen::writeGameTime()
{

	string quarterOutput = "Q" + to_string(quarter);
	string timeOutput = to_string(minutesRemaining) + ":" + to_string(secondsRemaining);

	MatchScreen::timeRemainingLabel->setText(QString::fromStdString(timeOutput));
	MatchScreen::quarterLabel->setText(QString::fromStdString(quarterOutput));
}

//processes the rollover from one quarter to another
void MatchScreen::goToNextQuarter()
{
	writeMatchText("End of quarter");
	writeLineBreak();
	quarter++;

	minutesRemaining = 12;
	resetPlayerPosition();
	changeTeamPossession();
}

//updates the on screen player stats
void MatchScreen::updatePlayerStats()
{

	//write team one player stats to the screen
	MatchScreen::teamOnePGStats->setText(QString::fromStdString(teams.at(teamOne).getPlayer("PG")->getStatline()));
	MatchScreen::teamOneSGStats->setText(QString::fromStdString(teams.at(teamOne).getPlayer("SG")->getStatline()));
	MatchScreen::teamOneSFStats->setText(QString::fromStdString(teams.at(teamOne).getPlayer("SF")->getStatline()));
	MatchScreen::teamOnePFStats->setText(QString::fromStdString(teams.at(teamOne).getPlayer("PF")->getStatline()));
	MatchScreen::teamOneCStats->setText(QString::fromStdString(teams.at(teamOne).getPlayer("C")->getStatline()));

	//write team two player stats to the screen
	MatchScreen::teamTwoPGStats->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("PG")->getStatline()));
	MatchScreen::teamTwoSGStats->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("SG")->getStatline()));
	MatchScreen::teamTwoSFStats->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("SF")->getStatline()));
	MatchScreen::teamTwoPFStats->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("PF")->getStatline()));
	MatchScreen::teamTwoCStats->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("C")->getStatline()));

	
}

//updates the names of the players in the player stats box (for when players are subbed in and out)
void MatchScreen::updatePositionLabels()
{
	MatchScreen::teamOnePGLabel->setText(QString::fromStdString(teams.at(teamOne).getPlayer("PG")->getSurname()));
	MatchScreen::teamOneSGLabel->setText(QString::fromStdString(teams.at(teamOne).getPlayer("SG")->getSurname()));
	MatchScreen::teamOneSFLabel->setText(QString::fromStdString(teams.at(teamOne).getPlayer("SF")->getSurname()));
	MatchScreen::teamOnePFLabel->setText(QString::fromStdString(teams.at(teamOne).getPlayer("PF")->getSurname()));
	MatchScreen::teamOneCLabel->setText(QString::fromStdString(teams.at(teamOne).getPlayer("C")->getSurname()));

	
	MatchScreen::teamTwoPGLabel->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("PG")->getSurname()));
	MatchScreen::teamTwoSGLabel->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("SG")->getSurname()));
	MatchScreen::teamTwoSFLabel->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("SF")->getSurname()));
	MatchScreen::teamTwoPFLabel->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("PF")->getSurname()));
	MatchScreen::teamTwoCLabel->setText(QString::fromStdString(teams.at(teamTwo).getPlayer("C")->getSurname()));

}

//processess an unsuccessful shot
void MatchScreen::unsuccessfulShot()
{
	string output;
	Player *rebounder;
	bool playerOnTeamInPossession = false;

	output = "Shot unsuccessful";
	writeMatchText(output);

	//determines which player gets the rebound
	rebounder = determineReboundResult();

	//gives ball to the rebounder
	playerInPossession = rebounder;

	//increment rebound stat
	playerInPossession->increaseStats(rebounds, 1);

	//determine whether the rebound was an offensive or defensive rebound
	playerOnTeamInPossession = isPlayerOnTeam(playerInPossession, teamInPossession);

	if (playerOnTeamInPossession == true)
	{
		output = "Offensive rebound by " + playerInPossession->getFirstName() + " " + playerInPossession->getSurname();
		writeMatchText(output);
		resetShotClock();
		currentPlayOver = false;
	}
	else
	{
		currentPlayOver = true;
		output = "Defensive rebound by " + playerInPossession->getFirstName() + " " + playerInPossession->getSurname();
		writeMatchText(output);
	}


}

//determines which player gets the rebound after a missed shot
Player* MatchScreen::determineReboundResult()
{

	Player *rebounder;
	Team *reboundingTeam;
	int reboundChance;

	Player *tempOne;
	Player *tempTwo;
	vector<Player*> possibleRebounders;
	vector<int> rebounderChance;
	int rebounderPos;

	rebounder = NULL;
	


	//create empty vector of players
	//populate with list of players within x range of basket
	for (int i = 0; i < 5; i++)
	{
		//gives priority to the players on the team without possession
		if (teamInPossession->getID() == 0)
			tempOne = teams.at(teamTwo).getPlayer(i);
		else
			tempOne = teams.at(teamOne).getPlayer(i);

		tempTwo = teamInPossession->getPlayer(i);

		//checks the distance of players from the basket and adds them to the potential rebounders vector if they
		//are close
		if (teamInPossession->getID() == 0)
		{
			if (getDistBetweenPoints(tempOne->getScreenPosition(), court->getBasketPos("right")) < 12)
			{
				possibleRebounders.push_back(tempOne);
				tempOne->setReboundingChance((tempOne->getAttributes(rebounding) + tempOne->getHeight()) / 2);

				//add the rebounding chance of each rebounder to an adjacent vector
				//rebounderChance.push_back((tempOne->getAttributes(rebounding) + tempOne->getHeight()) / 2);
			}


			if (getDistBetweenPoints(tempTwo->getScreenPosition(), court->getBasketPos("right")) < 12)
			{
				possibleRebounders.push_back(tempTwo);
				tempTwo->setReboundingChance((tempTwo->getAttributes(rebounding) + tempTwo->getHeight()) / 2);
				//rebounderChance.push_back((tempTwo->getAttributes(rebounding) + tempTwo->getHeight()) / 2);
			}
		}
		else
		{
			if (getDistBetweenPoints(tempOne->getScreenPosition(), court->getBasketPos("left")) < 12)
			{
				possibleRebounders.push_back(tempOne);
				tempOne->setReboundingChance((tempOne->getAttributes(rebounding) + tempOne->getHeight()) / 2);
				//rebounderChance.push_back((tempOne->getAttributes(rebounding) + tempOne->getHeight()) / 2);
			}

			if (getDistBetweenPoints(tempTwo->getScreenPosition(), court->getBasketPos("left")) < 12)
			{
				possibleRebounders.push_back(tempTwo);
				tempTwo->setReboundingChance((tempTwo->getAttributes(rebounding) + tempTwo->getHeight()) / 2);
				//rebounderChance.push_back((tempTwo->getAttributes(rebounding) + tempTwo->getHeight()) / 2);
			}
		}

	}

	//sort rebounders vector
	for (int z = 0; z < possibleRebounders.size(); z++)
	{
		for (int y = 0; y < possibleRebounders.size() - 1; y++)
		{

			if (possibleRebounders.at(y)->getReboundingChance() < possibleRebounders.at(y+1)->getReboundingChance())
			{

				int temp = possibleRebounders.at(y + 1)->getReboundingChance();

				possibleRebounders.at(y + 1)->setReboundingChance(possibleRebounders.at(y)->getReboundingChance());

				possibleRebounders.at(y)->setReboundingChance(temp);
			}
		}
	}
	

	//iterate through the possibleRebounders vector until a succesful rebounder is found
	for (int x = 0; x < possibleRebounders.size(); x++)
	{
		reboundChance = generateNumber(300, 1);

		if (reboundChance < possibleRebounders.at(x)->getReboundingChance())
		{
			rebounder = possibleRebounders.at(x);
			break;
		}
	}

	//if there are no players within a certain distance of the basket then randomly select a player
	if (possibleRebounders.size() == 0)
	{
		rebounder = teamInPossession->calculateRebounder(generateNumber(5, 1));

	}

	//if no rebounder is determined through above methods, set to first possible rebounder
	if (rebounder == NULL)
	{
		rebounder = possibleRebounders.at(0);
	}
	

	return rebounder;

}

//checks if x player is on x team
bool MatchScreen::isPlayerOnTeam(Player* playerToCheck, Team* teamToCheck)
{
	bool playerOnTeam = false;

	for (int i = 0; i < 5; i++)
	{
		if (playerToCheck->getID() == teamToCheck->getPlayer(i)->getID()) 
		{
			playerOnTeam = true;
		}
	}

	return playerOnTeam;
}

//simulate the tip off at the start of the game
void MatchScreen::runTipOff()
{
	//get the tallest player on each team
	Player *teamOneTallest = teams.at(teamOne).getTipOffPlayer();
	Player *teamTwoTallest = teams.at(teamTwo).getTipOffPlayer();

	int teamOneChanceOfWinning = 50;
	int randomNum;

	//weight the chance of winning according to the heights of the two players
	if (teamOneTallest->getHeight() > teamTwoTallest->getHeight())
	{
		teamOneChanceOfWinning += teamOneTallest->getHeight() - teamTwoTallest->getHeight();
	}
	else
	{
		teamOneChanceOfWinning -= teamTwoTallest->getHeight() - teamOneTallest->getHeight();
	}

	//prevents the odds of a team winning from becoming too overwhelming
	if (teamOneChanceOfWinning > 80)
		teamOneChanceOfWinning = 80;

	if (teamOneChanceOfWinning < 20)
		teamOneChanceOfWinning = 20;

	randomNum = generateNumber(100, 1);

	//determines which team wins the tip off
	if (randomNum < teamOneChanceOfWinning)
	{
		writeMatchText("Tip off won by team one");
		playerInPossession = teamOneTallest;
		teamInPossession = &teams.at(teamOne);
	}
	else
	{
		writeMatchText("Tip off won by team two");
		playerInPossession = teamTwoTallest;
		teamInPossession = &teams.at(teamTwo);
	}

}

//calculates the chance of a shot being successful
int MatchScreen::getShotChance()
{
	Player *defender;
	int shootingSkill;
	int distFromBasket = (int)playerInPossession->getDistFromBasket();
	int distFromDefender; 
	int fieldGoalPercentage = (int)playerInPossession->getFieldGoalPercentage();
	int defenderAbility;
	int height = playerInPossession->getHeight();
	int defenderHeight;
	int playerEnergy = playerInPossession->getAttributes(energy);
	int chanceOfSuccess;

	for (int i = 0; i < 2; i++)
	{
		//get the player defending the shooter
		if (teamInPossession->getID() != teams.at(i).getID())
			defender = teams.at(i).getPlayer(playerInPossession->getPosition());
	}

	defenderAbility = defender->getAttributes(defending);
	defenderHeight = defender->getHeight();
	distFromDefender = getDistBetweenPlayers(playerInPossession, defender);

	//determine which of the players shooting attributes to use
	if (distFromBasket <=12)
	{
		shootingSkill = playerInPossession->getAttributes(closeShooting);
		if (distFromDefender < 4)
			defenderAbility = defender->getAttributes(blocking);
	}
	else if (distFromBasket > 12 && distFromBasket <= 20)
	{
		shootingSkill = playerInPossession->getAttributes(midShooting);
	}
	else if (distFromBasket > 20)
	{
		shootingSkill = playerInPossession->getAttributes(threePointShooting);
	}

	//initialise chance of success to the players shooting skill
	chanceOfSuccess = shootingSkill;

	//increase the chance of success by a scaled version of the field goal percentage
	//this adds an aspect of 'confidence' - a player who is shooting well is more
	//likely to make a shot
	if (fieldGoalPercentage > 0)
		chanceOfSuccess += fieldGoalPercentage / 10;

	//reduce the chance of success due to the fatigue of the players and the distance they are from the basket
	chanceOfSuccess -= (100 - playerEnergy) / 10;
	chanceOfSuccess -= distFromBasket;

	//affect the chance of success positively/negatively depending on whether
	//the shooter is taller than the defender
	chanceOfSuccess += (height - defenderHeight);

	//reduce the chance of success by the defenders ability divided by how close the defender is to the player
	if (distFromDefender > 1)
		chanceOfSuccess -= (defenderAbility / distFromDefender);
	else
		chanceOfSuccess -= (defenderAbility / 2);
	

	return chanceOfSuccess;
}

//get the chance of a pass being successful
int MatchScreen::getPassChance(Player* teammate)
{
	Player *defender;

	for (int i = 0; i < 2; i++)
	{
		if (teamInPossession->getID() != teams.at(i).getID())
			defender = teams.at(i).getPlayer(teammate->getPosition());
	}

	int passingSkill = playerInPossession->getAttributes(passing);
	int distFromTeammate = 8;
	int teammateDistFromDefender = 6; //set to getdistfromdefender later
	int teammateDefenderAbility = defender->getAttributes(defending);
	int playerEnergy = playerInPossession->getAttributes(energy);
	int chanceOfSuccess = 100;


	chanceOfSuccess -= (teammateDefenderAbility / teammateDistFromDefender) + (passingSkill / distFromTeammate) - ((100 - playerEnergy) / 10);

	return chanceOfSuccess;
}

//get the chance of a drive being successful 
int MatchScreen::getDriveChance()
{
	Player *defender;

	for (int i = 0; i < 2; i++)
	{
		if (teamInPossession->getID() != teams.at(i).getID())
			defender = teams.at(i).getPlayer(playerInPossession->getPosition());
	}

	int drivingSkill = playerInPossession->getAttributes(dribbling);
	int playerAthleticism = playerInPossession->getAttributes(athleticism);
	int defenderAbility = defender->getAttributes(defending);
	int defenderAthleticism = defender->getAttributes(athleticism);
	int playerEnergy = playerInPossession->getAttributes(energy);
	int defenderEnergy = defender->getAttributes(energy);
	int chanceOfSuccess = 50;

	chanceOfSuccess += (drivingSkill + playerAthleticism) - (defenderAbility + defenderAthleticism);

	chanceOfSuccess -= (100 - playerEnergy) / 10;

	return chanceOfSuccess;
}

//display the 2D representation of the match
void MatchScreen::renderMatch()
{
	
	//update the players with the flag notifying them that it is being called 30 times a second
	teams.at(teamOne).updatePlayers(true);
	teams.at(teamTwo).updatePlayers(true);

	//move the players
	teams.at(teamOne).movePlayers();
	teams.at(teamTwo).movePlayers();

	//update the owner of the ball
	if (playerInPossession != NULL)
	{
		ball->setOwner(playerInPossession);
		ball->update();
	}

	//display the match on screen
	MatchScreen::gameView->setScene(scene);
	MatchScreen::gameView->show();

}


//sets the defensive assignments for players
void MatchScreen::setDefensiveAssignments()
{
	teams.at(teamOne).setDefensiveAssignments(&teams.at(teamTwo));
	teams.at(teamTwo).setDefensiveAssignments(&teams.at(teamOne));
}