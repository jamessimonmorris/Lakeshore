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
	Windmill(GLuint, GLuint, GLuint, GLuint);                                 // constructor
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

	bool toTextureB = false, toTextureR = false, toTextureW = false, toTextureF = false;
	GLuint texidB, texidR, texidW, texidF;

	int rotors = 4;
};
#endif
