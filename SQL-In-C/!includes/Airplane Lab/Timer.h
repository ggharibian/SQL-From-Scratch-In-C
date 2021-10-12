#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <cassert>
using namespace std;

class Timer
{
public:
	//Constructor
	Timer(unsigned int numSecondsRequired);

	//Increment Time Function
	void OneSecond();

	//Reset Function
	void Reset();

	//State Function
	bool isBusy();

	//Setter Function
	void setEmpty();

private:

	unsigned int _numSecondsRequired; //Number of seconds that a plane must 
									  //remain in a specific state.
	unsigned int _numSecondsLeft;	  //Number of seconds remaining in that 
									  //state.

};


#endif // !TIMER_H
