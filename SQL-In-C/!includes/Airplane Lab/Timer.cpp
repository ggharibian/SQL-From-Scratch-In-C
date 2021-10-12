#include "Timer.h"

//------------------------------------------
//Constructor
//------------------------------------------

Timer::Timer(unsigned int numSecondsRequired) : _numSecondsRequired(numSecondsRequired), _numSecondsLeft(0) {}

//------------------------------------------
//Increment Time Function
//------------------------------------------

void Timer::OneSecond()
{
	if (isBusy()) {
		_numSecondsLeft--;
	}
}

//------------------------------------------
//Reset Function
//------------------------------------------

void Timer::Reset()
{
	_numSecondsLeft = _numSecondsRequired;
}

//------------------------------------------
//State Function
//------------------------------------------

bool Timer::isBusy()
{
	return _numSecondsLeft != 0;
}

//------------------------------------------
//Setter Function
//------------------------------------------

void Timer::setEmpty()
{
	_numSecondsLeft = 0;
}
