#ifndef ___House__
#define ___House__

#include "DisplayableObject.h"
#include <string>

using namespace std;

class House :
	public DisplayableObject
{
public:
	House(int, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
	House(int);
	~House();
	void display();

private:
	void drawWall();
	void drawRoof();

	bool toTextureR = false, toTexture1 = false, toTexture2 = false, toTexture3 = false, toTexture4 = false, toTextureD1 = false, toTextureD2 = false, toTextureD3 = false, toTextureG1 = false, toTextureG2 = false;
	GLuint texidR, texid1, texid2, texid3, texid4, texidD1, texidD2, texidD3, texidG1, texidG2;		// texture values (Roof, brick, church, House2, House3, Door1, Door2, Door3, Garage1, Garage2
	int ranNum, choice = 0;		// Random num gen // house choice (selected by ranNum modulus)
	float texCoord;				// Differing texture coord, dependent on different wall textures
};

#endif
