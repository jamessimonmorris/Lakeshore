#ifndef ___Windmill__
#define ___Windmill__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <cmath>
#include <cstdio>

using namespace std;

class Windmill : public DisplayableObject, public Animation       // a Windmill is a DisplayableObject and Animation
{
public:
	Windmill(GLuint, GLuint, GLuint, GLuint, GLuint);                                 // constructor
	Windmill();
	~Windmill() { };                            // destructor
	void display();                         // overloaded virtual display function
	void update(float dT);

	void setRotors(int);
	int getRotors();
private:
	float aT, animationTime;
	float angle;

	void drawWindmill();
	void drawBase(float);                          // draw base function
	void drawRoof(float);
	void drawRotors();
	void drawRotor();

	bool toTextureB = false, toTextureR = false, toTextureW = false, toTextureF = false, toTextureM = false;
	GLuint texidB, texidR, texidW, texidF, texidM;			// texture supporting variables (Base, Roof, Wood, Fabric, Metal)

	double speed = 0.0074444;		// rotor speed
	int rotors = 6;					// default number of rotors
};
#endif
