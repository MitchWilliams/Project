#pragma once

#include <vector>
#include "Player.h"


enum positions{ pointGuard, shootingGuard, smallForward, powerForward, center, POSITIONS_MAX = center };
enum coachcommands { driveMore, passMore, shootThrees, defendAgressively, playFaster, COMMANDS_MAX = playFaster };

class MatchInfo;

//The teams within the game
class Team : public BasketballStats
{
private:
	int teamID;
	bool isAITeam;
	vector<Player*> playersOnCourt; //vector with pointers to the players that are on the court
	vector<Player*> subPlayers; //not currently used
	int timeoutsRemaining; //not currently used
	vector <bool> coachCommands; //vector containing bools that say whether or not each command is active (not yet implemented)
	MatchInfo* matchInfo; //pointer to an instance of matchInfo
	

public:
	//void makeSubstition(Player* playerOn, Player* playerOff);
	//void takeTimeout();
	Team(vector<Player*> players, bool nAiTeam, int nTeamID, MatchInfo* nInfo);
	void updatePlayers(bool runOnlyFrequentStates);

	int getPlayerDecisions();
	Player* getPointGuard();
	Player* getPlayer(int vectorPos);
	Player* getPlayer(string playerPosition);
	Player* getTipOffPlayer();
	int getID(){ return teamID; }
	bool getInPossession();

	void setStartPositions();
	void setStartStates();
	void setPlayerInPossession(Player* nPlayer);
	void setDefensiveAssignments(Team* oppositionTeam);
	void setPlayerDefaultRegions(MatchInfo* nInfo);

	Player* calculateRebounder(int randomNum);
	void resetPlayerStats();
	void movePlayers();
};
