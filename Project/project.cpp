#include "project.h"


Project::Project(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.playMatchButton->setEnabled(false);
	ui.playMatchButton->setVisible(false);
	ui.teamOneAdd->setEnabled(false);
	ui.teamOneRemove->setEnabled(false);
	ui.teamTwoAdd->setEnabled(false);
	ui.teamTwoRemove->setEnabled(false);
	teamOneFull = false;
	teamTwoFull = false;
	twoHasPG = false;
	twoHasSG = false;
	twoHasSF = false;
	twoHasPF = false;
	twoHasC = false;
	oneHasPG = false;
	oneHasSG = false;
	oneHasSF = false;
	oneHasPF = false;
	oneHasC = false;

}

Project::~Project()
{

}

//loads the players into the player pool from the database
void Project::on_loadButton_clicked()
{
	//calls the function with the sql query to get everything from the player table
	dh.handlesql("basketballdb.db", "SELECT * FROM PLAYERTABLE");

	//populate the player vector with players
	playerPool = dh.populatePlayerPool(playerPool);

	//create new list items for every player in the vector
	for (int i = 0; i < playerPool.size(); i++)
	{
		playerFirstName = QString::fromStdString(playerPool.at(i)->getFirstName());
		playerSurname = QString::fromStdString(playerPool.at(i)->getSurname());
		playerName = playerFirstName + " " + playerSurname;
		playerID = QString::number(playerPool.at(i)->getID());

		QListWidgetItem *item = new QListWidgetItem(playerName, ui.playerPool);
		//attach the player ID as a piece of data linked to the list item
		item->setData(Qt::UserRole, playerID);
		ui.playerPool->setCurrentItem(item);
	}

	//disable the load button and enable the add buttons
	ui.loadButton->setEnabled(false);
	ui.teamOneAdd->setEnabled(true);
	ui.teamTwoAdd->setEnabled(true);
	

	
}

//updates the player information displayed when new player is selected
void Project::on_playerPool_currentItemChanged()
{
	QListWidgetItem *curItem = ui.playerPool->currentItem();
	
	int row;
	int idToLookFor;
	playerAttribs.clear();

	

	if (curItem)
	{
		//extracts the player ID from the list item
		idToLookFor = curItem->data(Qt::UserRole).toInt(); 

		//finds the player within the player vector
		for (int x = 0; x < playerPool.size(); x++)
		{
			if (playerPool.at(x)->getID() == idToLookFor)
				row = x;
		}

		//retrieve the information about the selcted player
		playerFirstName = QString::fromStdString(playerPool.at(row)->getFirstName());
		playerSurname = QString::fromStdString(playerPool.at(row)->getSurname());
		playerHeight = QString::number(playerPool.at(row)->getHeight());
		playerPosition = QString::fromStdString(playerPool.at(row)->getPosition());
			
		for (int i = 0; i < ATTRIBUTES_MAX; i++)
		{
			playerAttribs.push_back(QString::number(playerPool.at(row)->getAttributes(i)));
		}

		//update the labels with the new player information
		ui.firstNameField->setText(playerFirstName);
		ui.surnameField->setText(playerSurname);
		ui.heightField->setText(playerHeight);
		ui.positionField->setText(playerPosition);
		ui.closeField->setText(playerAttribs.at(closeShooting));
		ui.mediumField->setText(playerAttribs.at(midShooting));
		ui.threeField->setText(playerAttribs.at(threePointShooting));
		ui.passingField->setText(playerAttribs.at(passing));
		ui.dribblingField->setText(playerAttribs.at(dribbling));
		ui.reboundingField->setText(playerAttribs.at(rebounding));
		ui.defendingField->setText(playerAttribs.at(defending));
		ui.blockingField->setText(playerAttribs.at(blocking));
		ui.staminaField->setText(playerAttribs.at(stamina));
		ui.athleticismField->setText(playerAttribs.at(athleticism));

	}

	checkButtons();
}

//adds a player to team one
void Project::on_teamOneAdd_clicked()
{
	//remove player name and position from player pool list
	//put player name and position in team one list
	//add pointer to player in team one list

	Player *tempPlayer;
	
	
	QListWidgetItem *curItem = ui.playerPool->currentItem();
	int row;

	int idToLookFor;

	idToLookFor = curItem->data(Qt::UserRole).toInt(); 

	for (int x = 0; x < playerPool.size(); x++)
	{
		if (playerPool.at(x)->getID() == idToLookFor)
			row = x;
	}

	if (curItem)
	{

		//code partially taken from: http://qt-project.org/forums/viewthread/2610
		//to help with error
		//clone item
		QListWidgetItem *newItem = ui.playerPool->currentItem()->clone();
		//add new item to teamOnePool
		ui.teamOnePlayers->addItem(newItem);
		ui.teamOnePlayers->setCurrentItem(newItem);

		//delete old item from player pool
		delete ui.playerPool->currentItem();

		//tell the player what team it's on and set its image filepath
		tempPlayer = playerPool.at(row);
		tempPlayer->setFilePath("teamOnePlayers.jpg");
		tempPlayer->setTeamPlayingOn(1);
		tempTeamOne.push_back(tempPlayer);

		//change the bool variable telling the game if the team has a player in a certain position
		if (tempPlayer->getPosition() == "PG")
			oneHasPG = true;
		if (tempPlayer->getPosition() == "SG")
			oneHasSG = true;
		if (tempPlayer->getPosition() == "SF")
			oneHasSF = true;
		if (tempPlayer->getPosition() == "PF")
			oneHasPF = true;
		if (tempPlayer->getPosition() == "C")
			oneHasC = true;
		
		
	}

	checkButtons();
}

//adds players to team two
void Project::on_teamTwoAdd_clicked()
{
	//remove player name and position from player pool list
	//put player name and position in team one list
	//add pointer to player in team one list

	Player *tempPlayer;

	QListWidgetItem *curItem = ui.playerPool->currentItem();
	
	int row;

	int idToLookFor;

	idToLookFor = curItem->data(Qt::UserRole).toInt(); 

	for (int x = 0; x < playerPool.size(); x++)
	{
		if (playerPool.at(x)->getID() == idToLookFor)
			row = x;
	}

	if (curItem)
	{

		//code partially taken from: http://qt-project.org/forums/viewthread/2610
		//to help with error
		QListWidgetItem *newItem = ui.playerPool->currentItem()->clone();
		ui.teamTwoPlayers->addItem(newItem);
		ui.teamTwoPlayers->setCurrentItem(newItem);
		delete ui.playerPool->currentItem();

		tempPlayer = playerPool.at(row);
		tempPlayer->setFilePath("teamTwoPlayers.jpg");
		tempPlayer->setTeamPlayingOn(2);
		tempTeamTwo.push_back(tempPlayer);

		if (tempPlayer->getPosition() == "PG")
			twoHasPG = true;
		if (tempPlayer->getPosition() == "SG")
			twoHasSG = true;
		if (tempPlayer->getPosition() == "SF")
			twoHasSF = true;
		if (tempPlayer->getPosition() == "PF")
			twoHasPF = true;
		if (tempPlayer->getPosition() == "C")
			twoHasC = true;

	}


	checkButtons();
}

//load the match screen
void Project::on_playMatchButton_clicked()
{
	matchScreen = new MatchScreen(this);
	matchScreen->createTeams(tempTeamOne, tempTeamTwo);

	matchScreen->show();
	matchScreen->raise();
	matchScreen->activateWindow();
	
	
	//hide();
}

//remove a player from team one
void Project::on_teamOneRemove_clicked()
{
	QListWidgetItem *curItem = ui.teamOnePlayers->currentItem();
	Player *tempPlayer;
	int row;

	int idToLookFor;

	idToLookFor = curItem->data(Qt::UserRole).toInt(); 

	for (int x = 0; x < tempTeamOne.size(); x++)
	{
		if (tempTeamOne.at(x)->getID() == idToLookFor)
			row = x;
	}

	if (curItem)
	{

		//code partially taken from: http://qt-project.org/forums/viewthread/2610
		//to help with error
		QListWidgetItem *newItem = ui.teamOnePlayers->currentItem()->clone();
		ui.playerPool->addItem(newItem);
		ui.playerPool->setCurrentItem(newItem);
		delete ui.teamOnePlayers->currentItem();

		//reset the player team data and remove from the vector
		tempPlayer = tempTeamOne.at(row);
		tempPlayer->setFilePath("");
		tempPlayer->setTeamPlayingOn(0);
		tempTeamOne.erase(tempTeamOne.begin()+row);

		oneHasPG = false;
		oneHasSG = false;
		oneHasSF = false;
		oneHasPF = false;
		oneHasC = false;

		for (int x = 0; x < tempTeamOne.size(); x++)
		{
			if (tempTeamOne.at(x)->getPosition() == "PG")
				oneHasPG = true;
			if (tempTeamOne.at(x)->getPosition() == "SG")
				oneHasSG = true;
			if (tempTeamOne.at(x)->getPosition() == "SF")
				oneHasSF = true;
			if (tempTeamOne.at(x)->getPosition() == "PF")
				oneHasPF = true;
			if (tempTeamOne.at(x)->getPosition() == "C")
				oneHasC = true;
		}

			
	}
	checkButtons();
}

//removes players from team two
void Project::on_teamTwoRemove_clicked()
{
	QListWidgetItem *curItem = ui.teamTwoPlayers->currentItem();
	Player *tempPlayer;
	int row;

	int idToLookFor;

	idToLookFor = curItem->data(Qt::UserRole).toInt(); //possibly need another bracket

	for (int x = 0; x < tempTeamTwo.size(); x++)
	{
		if (tempTeamTwo.at(x)->getID() == idToLookFor)
			row = x;
	}

	if (curItem)
	{

		//code partially taken from: http://qt-project.org/forums/viewthread/2610
		//to help with error
		QListWidgetItem *newItem = ui.teamTwoPlayers->currentItem()->clone();
		ui.playerPool->addItem(newItem);
		ui.playerPool->setCurrentItem(newItem);
		delete ui.teamTwoPlayers->currentItem();

		tempPlayer = tempTeamTwo.at(row);
		tempPlayer->setFilePath("");
		tempPlayer->setTeamPlayingOn(0);
		tempTeamTwo.erase(tempTeamTwo.begin() + row);

			twoHasPG = false;
			twoHasSG = false;
			twoHasSF = false;
			twoHasPF = false;
			twoHasC = false;

		for (int x = 0; x < tempTeamTwo.size(); x++)
		{
			if (tempTeamTwo.at(x)->getPosition() == "PG")
				twoHasPG = true;
			if (tempTeamTwo.at(x)->getPosition() == "SG")
				twoHasSG = true;
			if (tempTeamTwo.at(x)->getPosition() == "SF")
				twoHasSF = true;
			if (tempTeamTwo.at(x)->getPosition() == "PF")
				twoHasPF = true;
			if (tempTeamTwo.at(x)->getPosition() == "C")
				twoHasC = true;
		}
		
	}

	checkButtons();
}

//enable/disable the buttons as needed
void Project::checkButtons()
{

	if (twoHasPG == true && twoHasSG == true && twoHasSF == true && twoHasPF == true && twoHasC == true)
		teamTwoFull = true;
	else
		teamTwoFull = false;

	if (oneHasPG == true && oneHasSG == true && oneHasSF == true && oneHasPF == true && oneHasC == true)
		teamOneFull = true;
	else
		teamOneFull = false;

	//only enable the play match button when both teams have one player for each position
	if (teamOneFull == true && teamTwoFull == true)
	{
		ui.playMatchButton->setEnabled(true);
		ui.playMatchButton->setVisible(true);
		ui.warningLabel->setVisible(false);
	}
	else
	{
		ui.playMatchButton->setEnabled(false);
		ui.playMatchButton->setVisible(false);
		ui.warningLabel->setVisible(true);
	}

	//disable the add buttons if the player pool is empty
	if (ui.playerPool->count() < 1)
	{
		ui.teamOneAdd->setEnabled(false);
		ui.teamTwoAdd->setEnabled(false);
	}
	else
	{
		ui.teamOneAdd->setEnabled(true);
		ui.teamTwoAdd->setEnabled(true);
	}

	//disable the remove buttons if there are no players on the team
	if (ui.teamOnePlayers->count() < 1)
	{
		ui.teamOneRemove->setEnabled(false);
	}
	else
	{
		ui.teamOneRemove->setEnabled(true);
	}

	if (ui.teamTwoPlayers->count() < 1)
	{
		ui.teamTwoRemove->setEnabled(false);
	}
	else
	{
		ui.teamTwoRemove->setEnabled(true);
	}

}