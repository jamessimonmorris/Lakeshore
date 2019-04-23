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
#include "Stage.h"
#include "Windmill.h"
#include "Tree.h"
#include "TreeLong.h"
#include <string>
#include <map>
#include "TextureManager.h"

void setup();
float runtime();
void reshape(int, int);
void draw();
float randomNumGen();
void checkGLError();						// Prints any OpenGL errors to console
void destroyObjects();
int main(int argc, char **argv);

int width, height, prevTime;
map<string, DisplayableObject*> objects;
float camrad, camangle = -0.785398f, zoom = 24.f, camh = 45.f;
float eye[3];
float cen[3];

void setGlobalLight();
void positionCamera();
void cameraRadius();
void keyPressed(int, int, int);
void keyPressed(unsigned char, int, int);

float ranNum;
bool ortho = false;
int scale = 75.f;

#endif
