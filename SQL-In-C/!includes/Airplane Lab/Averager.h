#ifndef AVERAGER_H
#define AVERAGER_H

class Averager
{
public:

	//Constructor
	Averager();

	//Mutator Function
	void nextNumber(double value);

	//Accessor Function
	size_t howManyNumbers() const { return _count; }

	//Accessor Function
	double average() const;

private:
	size_t _count; //Number of elements
	double _sum;   //Sum of current elements
};


#endif // !AVERAGER_H
