#ifndef ___House__
#define ___House__

#include "DisplayableObject.h"
#include <string>

using namespace std;

class House :
	public DisplayableObject
{
public:
	House(int, GLuint, GLuint, GLuint, GLuint, GLuint);
	House(int);
	~House();
	void display();

private:
	void drawWall();
	void drawRoof();

	bool toTextureR = false, toTexture1 = false, toTexture2 = false, toTexture3 = false, toTexture4 = false;
	GLuint texidR, texid1, texid2, texid3, texid4;
	int ranNum, choice = 0;
	float texCoord;
};

#endif
