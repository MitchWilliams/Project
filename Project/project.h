#ifndef PROJECT_H
#define PROJECT_H

#include <QtWidgets/QMainWindow>
#include "ui_project.h"
#include "GameControllers.h"
#include "matchscreen.h"

class Project : public QMainWindow
{
	Q_OBJECT

public:
	Project(QWidget *parent = 0);
	~Project();

private:
	Ui::ProjectClass ui;
	MatchScreen *matchScreen;
	PlayerDatabaseHandler dh;
	vector<Player*> playerPool;
	vector<Player*> tempTeamOne;
	vector<Player*> tempTeamTwo;
	QString playerFirstName;
	QString playerSurname;
	QString playerHeight;
	QString playerName;
	QTimer *screenTimer;
	QString playerPosition;
	QString playerID;
	vector<QString> playerAttribs;
	bool teamOneFull;
	bool teamTwoFull;
	bool twoHasPG, twoHasSG, twoHasSF, twoHasPF, twoHasC;
	bool oneHasPG, oneHasSG, oneHasSF, oneHasPF, oneHasC;

	void addPlayer();
	void checkButtons();

private slots:
	void on_loadButton_clicked();
	void on_playerPool_currentItemChanged();
	void on_teamOneAdd_clicked();
	void on_teamTwoAdd_clicked();
	void on_playMatchButton_clicked();
	void on_teamOneRemove_clicked();
	void on_teamTwoRemove_clicked();
};

#endif // PROJECT_H
