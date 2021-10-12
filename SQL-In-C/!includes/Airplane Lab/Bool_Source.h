#ifndef BOOL_SOURCE
#define BOOL_SOURCE

#include <cassert>
#include <random>
#include <ctime>
using namespace std;

class Bool_Source
{
public:
	//Constructor
	Bool_Source(double probability = 0.5);

	//Probability Query function
	bool Query() const;

private:
	double _probability; //probability of something happening.
};


#endif // !BOOL_SOURCE