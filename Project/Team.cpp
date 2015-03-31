#include "Team.h"

//Team code

Team::Team(vector<Player*> players, bool nAiTeam, int nTeamID, MatchInfo* nInfo)
{
	isAITeam = nAiTeam;
	teamID = nTeamID;
	matchInfo = nInfo;

	if (players.size() > 5)
	{
		//code for when I add substitutions
	}
	else
	{
		playersOnCourt = players;
	}


	timeoutsRemaining = 8;

	for (int i = 0; i < COMMANDS_MAX; i++)
	{
		coachCommands.push_back(false);
	}

	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		playersOnCourt.at(i)->setMatchInfo(nInfo);
	}
}

//set the starting positions for each player
void Team::setStartPositions()
{

	Vector2D newPos;

	for (int i = 0; i < playersOnCourt.size(); i++)
	{	
		if (teamID == 0)
		{ 
			if (playersOnCourt.at(i)->getPosition() == "PG")
			{
				playersOnCourt.at(i)->setDistFromBasket(24);
				newPos.x = 210;
				newPos.y = 221;
			}
		
			if (playersOnCourt.at(i)->getPosition() == "SG")
			{
				playersOnCourt.at(i)->setDistFromBasket(22);
				newPos.x = 210;
				newPos.y = 132;
			}	

			if (playersOnCourt.at(i)->getPosition() == "SF")
			{
				playersOnCourt.at(i)->setDistFromBasket(22);
				newPos.x = 282;
				newPos.y = 77;
			}	

			if (playersOnCourt.at(i)->getPosition() == "PF")
			{
				playersOnCourt.at(i)->setDistFromBasket(16);
				newPos.x = 282;
				newPos.y = 268;
			}
		
			if (playersOnCourt.at(i)->getPosition() == "C")
			{		
				playersOnCourt.at(i)->setDistFromBasket(8);
				newPos.x = 282;
				newPos.y = 173;
			}
			
			
		}
		else
		{
			if (playersOnCourt.at(i)->getPosition() == "PG")
			{
				playersOnCourt.at(i)->setDistFromBasket(24);
				newPos.x = 240;
				newPos.y = 221;
			}

			if (playersOnCourt.at(i)->getPosition() == "SG")
			{
				playersOnCourt.at(i)->setDistFromBasket(22);
				newPos.x = 240;
				newPos.y = 132;
			}

			if (playersOnCourt.at(i)->getPosition() == "SF")
			{
				playersOnCourt.at(i)->setDistFromBasket(22);
				newPos.x = 312;
				newPos.y = 77;
			}

			if (playersOnCourt.at(i)->getPosition() == "PF")
			{
				playersOnCourt.at(i)->setDistFromBasket(16);
				newPos.x = 312;
				newPos.y = 268;
			}

			if (playersOnCourt.at(i)->getPosition() == "C")
			{
				playersOnCourt.at(i)->setDistFromBasket(8);
				newPos.x = 312;
				newPos.y = 173;
			}
		}

		playersOnCourt.at(i)->setScreenPosition(newPos);
	}

}

void Team::setStartStates()
{
	bool inPossession = getInPossession();

	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		if (inPossession == true)
		{
			playersOnCourt.at(i)->setState(attacking_state);
		}
		else
		{
			playersOnCourt.at(i)->setState(defending_state);
		}
	}
}

//update the players 
void Team::updatePlayers(bool runOnlyFrequentStates)
{
	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		playersOnCourt.at(i)->update();
	}

	
	playersOnCourt.at(0)->setStaticStateValues(runOnlyFrequentStates);
}

//gets the decision of the player in possession
int Team::getPlayerDecisions()
{

	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		if (playersOnCourt.at(i)->getID() == matchInfo->getPlayerInPossession()->getID())
			return playersOnCourt.at(i)->getOnBallAction();
	}


}

//returns the teams point guard
Player* Team::getPointGuard()
{
	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		if (playersOnCourt.at(i)->getPosition() == "PG")
			return playersOnCourt.at(i);

	}
}

//gets the player at a given position in the vector
Player* Team::getPlayer(int vectorPos)
{
	return playersOnCourt.at(vectorPos);
}

//gets the player at a given position
Player* Team::getPlayer(string playerPosition)
{
	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		if (playersOnCourt.at(i)->getPosition() == playerPosition)
			return playersOnCourt.at(i);

	}
}


void Team::setPlayerInPossession(Player* nPlayer)
{
	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		//if (playersOnCourt.at(i)->getID() == nPlayer->getID())
		//playersOnCourt.at(i)->gainPossession();

	}
}

//returns a random player 
Player* Team::calculateRebounder(int randomNum)
{
	int rebounderVectorPos;

	rebounderVectorPos = randomNum - 1;

	return playersOnCourt.at(rebounderVectorPos);
}

//returns the tallest player on the team
Player* Team::getTipOffPlayer()
{
	Player* tallestPlayer;

	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		if (i == 0)
			tallestPlayer = playersOnCourt.at(i);
		else
		{
			if (playersOnCourt.at(i)->getHeight() > tallestPlayer->getHeight())
				tallestPlayer = playersOnCourt.at(i);
		}
	}

	return tallestPlayer;
}

//resets the player stats
void Team::resetPlayerStats()
{
	Player *tempPlayer;

	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		playersOnCourt.at(i)->resetStats();
	}
}

//determines if the team is in possession or not
bool Team::getInPossession()
{
	if (matchInfo->getTeamInPossession()->getID() == teamID)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//sets the defensive assignments for each player
void Team::setDefensiveAssignments(Team* oppositionTeam)
{
	getPlayer("PG")->setPlayerToGuard(oppositionTeam->getPlayer("PG"));
	getPlayer("SG")->setPlayerToGuard(oppositionTeam->getPlayer("SG"));
	getPlayer("SF")->setPlayerToGuard(oppositionTeam->getPlayer("SF"));
	getPlayer("PF")->setPlayerToGuard(oppositionTeam->getPlayer("PF"));
	getPlayer("C")->setPlayerToGuard(oppositionTeam->getPlayer("C"));
}

//sets the default regions for each player
void Team::setPlayerDefaultRegions(MatchInfo *nInfo)
{
	if (teamID == 0)
	{
		getPlayer("PG")->setDefaultRegion(right_PG, nInfo->courtRegions);
		getPlayer("SG")->setDefaultRegion(right_SG, nInfo->courtRegions);
		getPlayer("SF")->setDefaultRegion(right_SF, nInfo->courtRegions);
		getPlayer("PF")->setDefaultRegion(right_PF, nInfo->courtRegions);
		getPlayer("C")->setDefaultRegion(right_C, nInfo->courtRegions);
	}
	else
	{
		getPlayer("PG")->setDefaultRegion(left_PG, nInfo->courtRegions);
		getPlayer("SG")->setDefaultRegion(left_SG, nInfo->courtRegions);
		getPlayer("SF")->setDefaultRegion(left_SF, nInfo->courtRegions);
		getPlayer("PF")->setDefaultRegion(left_PF, nInfo->courtRegions);
		getPlayer("C")->setDefaultRegion(left_C, nInfo->courtRegions);
	}
	
}

//moves the players
void Team::movePlayers()
{
	for (int i = 0; i < playersOnCourt.size(); i++)
	{
		playersOnCourt.at(i)->move();
	}
}