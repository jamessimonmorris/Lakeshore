#ifndef ___MyScene__
#define ___MyScene__
#ifdef __APPLE__ // if OS X
#include <glut/glut.h> // include freeglut libraries
#else // if Windows
#include <gl/glut.h> // include freeglut libraries
#endif

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Windmill.h"
#include "Tree.h"
#include <string>
#include <map>

void setup();
float runtime();
void reshape(int, int);
void draw();
void checkGLError();						// Prints any OpenGL errors to console
void destroyObjects();
int main(int argc, char **argv);

int width, height, prevTime;
map<string, DisplayableObject*> objects;
float camrad, camangle = 0.f;
float eye[3];
float cen[3];

void positionCamera();
void cameraRadius();
void keyPressed(int, int, int);
void keyPressed(unsigned char, int, int);

#endif
