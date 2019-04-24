#ifndef ___TreeLong__
#define ___TreeLong__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

class TreeLong : public DisplayableObject       // a Tree1 is a DisplayableObject
{
public:
	TreeLong(float, GLuint, GLuint);                                 // constructor
	TreeLong(float);
	~TreeLong() { };                            // destructor
	void display();                         // overloaded virtual display function
private:
	void trunk();                          // draw trunk function
	void leaves();

	float ranNum;
	int height;

	bool toTexture = false, toTextureL = false;
	GLuint texid, texidL;
};
#endif
