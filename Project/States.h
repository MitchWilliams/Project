#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class StateContext;
class Player;

//The different states a player can be in
class State
{
protected:
	StateContext* currentContext;
	static bool runOnlyFrequentStates;
public:
	State(StateContext *context){ currentContext = context; }

	
	virtual void execute(Player* player) = 0;
	void setFrequentStates(bool nValue){ runOnlyFrequentStates = nValue; }
};


//The state context
class StateContext
{
protected:
	State* currentState;
	vector<State*> availableStates;
public:
	void setState(int newState);
	
	

};



