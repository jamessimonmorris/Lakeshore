#ifndef ___Stage__
#define ___Stage__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "DisplayableObject.h"

class Stage : public DisplayableObject
{
public:
	Stage();
	~Stage() {};
	void display();

	void setTextures(GLuint* _texids);	// Setter to assign texture binding ids
private:
	void drawStage();

	bool toTexture = false;             // Flag to check if texture loaded correctly
	GLuint* texids;                     // Store a copy of the loaded texture binding id
};
#endif
