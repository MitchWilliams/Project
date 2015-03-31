#include "States.h"

using namespace std;

bool State::runOnlyFrequentStates = false;

void StateContext::setState(int newState)
{
	currentState = availableStates.at(newState);
}