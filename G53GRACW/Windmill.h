#ifndef ___Windmill__
#define ___Windmill__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>
#include <string>

using namespace std;

class Windmill : public DisplayableObject       // a Windmill is a DisplayableObject
{
public:
	Windmill();                                 // constructor
	~Windmill() { };                            // destructor
	void display();                         // overloaded virtual display function
private:
	void base();                          // draw base function
};
#endif
