#ifndef __MyScene__
#define __MyScene__
#ifdef __APPLE__ // if OS X
#include <glut/glut.h> // include freeglut libraries
#else // if Windows
#include <gl/glut.h> // include freeglut libraries
#endif

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Windmill.h"
#include <string>
#include <map>

void setup();
void reshape(int, int);
void draw();
int main(int argc, char **argv);
void checkGLError();						// Prints any OpenGL errors to console

int width, height;
map<string, DisplayableObject*> objects;

#endif
