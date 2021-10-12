#include "Airplane_Simulation.h"

//------------------------------------------
//Constructor
//------------------------------------------

Airplane_Simulation::Airplane_Simulation(unsigned int takeoffTime, 
	double takeoffProbability, unsigned int landingTime, 
	double landingProbability, unsigned int fuelLimit, 
	unsigned int totalTime): _takeoffTime(takeoffTime), 
	_takeoffProbability(takeoffProbability), _landingTime(landingTime), 
	_landingProbability(landingProbability), _fuelLimit(fuelLimit), 
	_totalTime(totalTime){}

//------------------------------------------
//Simulation Function
//------------------------------------------

void Airplane_Simulation::runSimulation(){

	cout << "============================================" << endl;
	cout << "time to take off      : " << _takeoffTime << endl;
	cout << "time to land          : " << _landingTime << endl;
	cout << "probability of landing: " << _landingProbability << endl;
	cout << "probability of takeoff: " << _takeoffProbability << endl;
	cout << "fuel : time to crash  : " << _fuelLimit << endl;
	cout << "total simulation time : " << _totalTime << endl;
	cout << endl << endl << endl 
		 << ". . . . . . . . . . . . . . . . . . . . . . ." << endl;

			//Console display of initial values for the simulation.

	Queue<unsigned int> takeoffTimes;
	Queue<unsigned int> landingTimes;

			//Queues filled with int times representing the time in the 
			//simulation where a plane entered the line for landing or taking
			//off.

	Bool_Source takeoffChance(_takeoffProbability);
	Bool_Source landingChance(_landingProbability);
			//Bool_Source objects that dictate whether a plane has arrived or 
			//not to the takeoff or landing queues

	Averager takeoffAverages;
	Averager landingAverages;
			//Averager objects that will take all the times spent in the queue for each
			//plane and return the average.

	Timer timeToTakeoff(_takeoffTime);
	Timer timeToLand(_landingTime);
			//Timer objects that record the amount of time that a plane has 
			//been undergoing a process (either landing or taking off)

	unsigned int next; //The next value to be added to the averager.

	unsigned int numPlanesCrashed = 0; //Number of crashed planes during 
									   //simulation.
	unsigned int numPlanesLanded = -1; //Number of planes that have landed.

	unsigned int numPlanesTakenOff = -1; //Number of planes that have taken 
										 //off.

	for (unsigned int currentTime = 0; currentTime <= _totalTime; currentTime++) {
				//The loop will repeat for a specified number of iterations, 
				//representing the number of minutes the simulation has been
				//active

		if (takeoffChance.Query())
					//Checks to see if a plane is taking off based on probability.
			takeoffTimes.Push(currentTime);
						//Pushes a new plane's time onto the takeoffTimes queue

		if (landingChance.Query())
					//Checks to see if a plane is landing based on probability.
			landingTimes.Push(currentTime);
						//Pushes a new plane's time onto the takeoffTimes queue

		while (!landingTimes.Empty() && (currentTime - landingTimes.Front()) >= _fuelLimit) {
					//While loop condition checks to see if a plane has run
					//out of fuel within the queue.

			landingTimes.Pop();
			numPlanesCrashed++;
			timeToLand.setEmpty();
					//If a plane runs out of fuel, it is discarded then the
					//timer is reset for the next plane.
		}

		if (!timeToTakeoff.isBusy() && !timeToLand.isBusy()) {
					//Checks to see if a plane is being worked on.

			if (!landingTimes.Empty()) {
					//If there are planes waiting to land.

				next = landingTimes.Pop();
				landingAverages.nextNumber(currentTime - next);
				timeToLand.Reset();
				numPlanesLanded++;
						//The previous plane's change in time is put into the
						//averager and the timer is reset for a new plane.
			}
			else if (!takeoffTimes.Empty())
			{		//If there are planes waiting to take off (only evaluates
					//when there are no planes trying to land)

				next = takeoffTimes.Pop();
				takeoffAverages.nextNumber(currentTime - next);
				timeToTakeoff.Reset();
				numPlanesTakenOff++;
						//The previous plane's change in time is put into the
						//averager and the timer is reset for a new plane.
			}

		}


		timeToTakeoff.OneSecond();
		timeToLand.OneSecond();
				//The timer's internal clock is decremented by one second.
	}

	//=========================The outputs are printed =======================
	cout << numPlanesLanded << " landed." << endl;
	cout << numPlanesTakenOff << " took off." << endl;

	switch (numPlanesCrashed) {

	case 0:
		cout << numPlanesCrashed << " planes crashed. :)" << endl;
		break;

	case 1:
		cout << numPlanesCrashed << " plane crashed. :(" << endl;
		break;

	default:
		cout << numPlanesCrashed << " planes crashed. :(" << endl;

	}

	cout << "Average Wait Time To Land: " << landingAverages.average() 
		<< endl;
	cout << "Average Wait Time To Take Off: " << takeoffAverages.average() 
		<< endl;
	cout << "Planes in landing queue: " << landingTimes.Size() << endl;
	cout << "Planes in take off queue: " << takeoffTimes.Size() << endl;
	cout << "============================================" << endl;
	//========================================================================
}
