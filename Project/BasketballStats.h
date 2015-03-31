#pragma once
#include <vector>

using namespace std;

enum stats{
	points, rebounds, assists, steals, blocks, fieldGoalAttempts, fieldGoalMakes, threePointAttempts,
	threePointMakes, freeThrowAttempts, freeThrowMakes, turnovers, STATS_MAX = turnovers
};

//class that contains the stats tracked during the match
class BasketballStats
{
protected:
	vector<int> objectStats;
public:
	BasketballStats();
	void increaseStats(int statToIncrease, int value);
	int getStats(int statToGet);
	void resetStats();

};