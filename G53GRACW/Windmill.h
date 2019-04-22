#ifndef ___Windmill__
#define ___Windmill__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <cmath>

using namespace std;

class Windmill : public DisplayableObject, public Animation       // a Windmill is a DisplayableObject and Animation
{
public:
	Windmill();                                 // constructor
	~Windmill() { };                            // destructor
	void display();                         // overloaded virtual display function
	void update(float dT);
private:
	float animationTime;

	void drawWindmill();
	void drawBase(float);                          // draw base function
	void drawRoof(float);
	void drawRotors();
	void drawRotor();
};
#endif
