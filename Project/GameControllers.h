#pragma once
#include <iostream>
#include <string>
#include <vector>
#//include "GameObjects.h"
//#include "States.h"
#include "Player.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "sqlite3.h"


using namespace std;

class DatabaseHandler
{
protected:

	int rowCounter;
public:
	DatabaseHandler();
	~DatabaseHandler();
	void handlesql(string databaseName, char *sqlCommand);
	virtual int callback(int argc, char **argv, char **azColName) = 0;


};

class PlayerDatabaseHandler : public DatabaseHandler
{
private:

	//int rowCounter;
	vector<Player*> tempPlayerPool;
public:

	vector<Player*> populatePlayerPool(vector<Player*> nPlayerPool);
	int callback(int argc, char **argv, char **azColName);
};

class RuleDatabaseHandler : public DatabaseHandler
{
private:
	string reccomendation;
public:
	int callback(int argc, char**argv, char **azColName);
	string getReccomendation(char *query);

};