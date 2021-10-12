#ifndef AIRPLANE_SIMULATION_H
#define AIRPLANE_SIMULATION_H

#include <iostream>
#include "Averager.h"
#include "Bool_Source.h"
#include "Timer.h"
#include "../Queue/Queue.h"
using namespace std;



class Airplane_Simulation
{
public:

    //Constructor

    Airplane_Simulation(unsigned int takeoffTime, double takeoffProbability,
        unsigned int landingTime, double landingProbability,
        unsigned int fuelLimit, unsigned int totalTime);

    //Simulation function
    void runSimulation();

private:
    unsigned int _takeoffTime;      //how long it takes for a take off once plane 
                                    //    is on the runway 
    double _takeoffProbability;     //probability of arrival of a plane into the 
                                    //    take off line 
    unsigned int _landingTime;      //how long it takes for a plane to land on the 
                                    //    runway in each second
    double _landingProbability;     //probability of arrival of planes for landing 
                                    //     in each second
    unsigned int _fuelLimit;        //maximum amount of time a plan can stay in 
                                    //      landing queue without crashing
    unsigned int _totalTime;        //total time you will run the simulation.
};


#endif // !AIRPLANE_SIMULATION_H
