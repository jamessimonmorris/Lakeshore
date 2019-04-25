#ifndef ___Sign__
#define ___Sign__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>

class Sign :
	public DisplayableObject
{
public:
	Sign(GLuint, GLuint, GLuint);
	Sign();
	~Sign();
	void display();
private:
	bool toTextureP = false, toTextureS = false, toTextureB = false;
	GLuint texidP, texidS, texidB;

	void drawSign();
	void drawPost(float, float);
	void drawBoard(float, float, float);
};

#endif
