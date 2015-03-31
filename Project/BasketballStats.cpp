#include "BasketballStats.h"

void BasketballStats::increaseStats(int statToIncrease, int value)
{
	objectStats.at(statToIncrease) += value;
}

int BasketballStats::getStats(int statToGet)
{
	return objectStats.at(statToGet);
}

BasketballStats::BasketballStats()
{
	//populate the stats vector with initial values of 0
	for (int i = 0; i <= STATS_MAX; i++)
	{
		objectStats.push_back(0);
	}
}

void BasketballStats::resetStats()
{
	for (int i = 0; i < STATS_MAX; i++)
	{
		objectStats.at(i) = 0;
	}
}