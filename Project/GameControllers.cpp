#include "GameControllers.h"
#include "string"

using namespace std;

//Database code

//Code for this function partially taken from:
//http://stackoverflow.com/questions/14437433/proper-use-of-callback-function-of-sqlite3-in-c
//calls the callback function for the relevant database handler class
static int c_callback(void *param, int argc, char **argv, char **azColName)
{
	DatabaseHandler* dbh = reinterpret_cast<DatabaseHandler*>(param);
	return dbh->callback(argc, argv, azColName);
}

DatabaseHandler::DatabaseHandler()
{
	rowCounter = 0;
	
}

DatabaseHandler::~DatabaseHandler()
{
	
}

//returns the vector of the players that have been loaded from the database
vector<Player*> PlayerDatabaseHandler::populatePlayerPool(vector<Player*> nPlayerPool)
{
	

	for (int i = 0; i < tempPlayerPool.size(); i++)
	{
		nPlayerPool.push_back(tempPlayerPool.at(i));
	}

	return tempPlayerPool;
}

void DatabaseHandler::handlesql(string databaseName, char *sqlCommand)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	char *sql;
	int rc;
	rowCounter = 0;

	//opens the database
	rc = sqlite3_open(databaseName.c_str(), &db);

	//sets the sql statement to be executed
	sql = sqlCommand;

	/* Execute SQL statement */
	//executes sql statement and performs the callback function on every record returned
	rc = sqlite3_exec(db, sql, c_callback, this, &zErrMsg);
	if (rc != SQLITE_OK){
		
		sqlite3_free(zErrMsg);
	}
	else{
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

	
}

int PlayerDatabaseHandler::callback(int argc, char **argv, char **azColName)
{
	Player *tempPlayer = new Player();
	vector <int> tempAttribs;
	string tempFirstName, tempSurname, tempPosition;
	int tempHeight, tempId;
	int attribPos;
	rowCounter++;
	int i;

	for (i = 0; i<argc; i++){
		//parse column values into temporary player
		
		switch (i)
		{
		case 0:
			tempId = atoi(argv[i]);
			break;
		case 1:
			tempFirstName = argv[i];
			break;
		case 2:
			tempSurname = argv[i];
			break;
		case 3:
			tempHeight = atoi(argv[i]);
			break;
		case 4:
			tempPosition = argv[i];
			break;
		default:
			break;
		
		}

		if (i > 4)
		{
			tempAttribs.push_back(atoi(argv[i]));
		}
	}

	//set the values of the temporary player
	tempPlayer->setAttributes(tempAttribs);
	tempPlayer->setInfo(tempFirstName, tempSurname, tempHeight, tempPosition, tempId);
	tempPlayerPool.push_back(tempPlayer);
	

	return 0;
	
}

int RuleDatabaseHandler::callback(int argc, char **argv, char **azColName)
{
	//retrieves the reccomendation from the database
	reccomendation = argv[0];

	return 0;
}

string RuleDatabaseHandler::getReccomendation(char* query)
{
	handlesql("ruledb.db", query);

	return reccomendation;
}



