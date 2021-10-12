#include "Averager.h"

//------------------------------------------
//Constructor
//------------------------------------------

Averager::Averager() : _sum(0), _count(0) {}

//------------------------------------------
//Mutator Function
//------------------------------------------

void Averager::nextNumber(double value)
{
	_count++;
	_sum += value;
			//The total sum and counts are modified to account for a new 
			//value.
}

//------------------------------------------
//Accessor Function
//------------------------------------------

double Averager::average() const
{
	return _sum/_count;
			//The average value is returned
}
