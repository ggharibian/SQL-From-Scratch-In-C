#include "Bool_Source.h"

//------------------------------------------
//Constructor
//------------------------------------------

Bool_Source::Bool_Source(double probability) : _probability(probability) 
{
	assert(probability >= 0 && probability <= 1);
	srand(time(NULL));
			//Seeds the rand to a time value.
}

//------------------------------------------
//Probability Query Function
//------------------------------------------

bool Bool_Source::Query() const
{
	return (rand() < _probability * RAND_MAX);
			//Returns either true or false based on the probability.
}
