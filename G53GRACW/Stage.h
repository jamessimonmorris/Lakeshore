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
private:
	void drawStage();
};
#endif
