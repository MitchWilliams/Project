#ifndef MATCHSCREEN_H
#define MATCHSCREEN_H

#include <QDialog>
#include "ui_matchscreen.h"
#include "GameControllers.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "MatchInfo.h"
#include "Ball.h"
#include <qgraphicsscene.h>




enum teams{ teamOne, teamTwo};



class MatchScreen : public QDialog, public Ui::MatchScreen, public MatchInfo
{
	Q_OBJECT
private:
	
	vector<Team> teams;
	
	int gameSpeed[4];
	
	bool currentPlayOver;
	bool gameOver;
	bool gamePaused;
	bool firstTimePlayClicked;

	QTimer *gameTimer;
	QTimer *renderTimer;
	QGraphicsScene *scene;
	QPainter *painter;
	
	
	int generateNumber(int max, int min);
	void runMatch();
	void changeTeamPossession();
	void givePossession(Player* nPlayer);
	void simPass();
	void simShot();
	void simDrive();
	void successfulShot();
	void writeLineBreak();
	void writeGameTime();
	void goToNextQuarter();
	void updatePlayerStats();
	void updatePositionLabels();
	Player* determineReboundResult();
	bool isPlayerOnTeam(Player* playerToCheck, Team* teamToCheck);
	void unsuccessfulShot();
	void resetPlayerPosition();
	void writeMatchText(string output);
	
	void resetShotClock(){ shotClockRemaining = 24; }
	void runTipOff();

	string getScore();
	int getShotChance();
	int getPassChance(Player* teammate);
	int getDriveChance();
	void setDefensiveAssignments();

	//void pauseMatch();
	//void continueMatch();
	//void timeout();

public:
	MatchScreen(QWidget *parent = 0);
	~MatchScreen();

	void createTeams(vector <Player*> nTeamOne, vector <Player*> nTeamTwo);
	

private slots:
	void on_playButton_clicked();
	void updateMatch();
	void renderMatch();
};

#endif // MATCHSCREEN_H
