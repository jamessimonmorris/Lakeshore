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
#include "Sign.h"
#include "House.h"
#include <string>
#include <map>
#include "TextureManager.h"
#include <iostream>

void setup();
float runtime();
void reshape(int, int);
void draw();
float randomNumGen();
void checkGLError();						// Prints any OpenGL errors to console
void destroyObjects();
int main(int argc, char **argv);

int width, height, prevTime;
static map<string, DisplayableObject*> objects;
float camrad, camangle = -0.785398f, zoom = 24.f, camh = 75.f;	// Instantiate values for camera functionality
float eye[3];
float cen[3];

void setGlobalLight();
void positionCamera();
void cameraRadius();
void keyPressed(int, int, int);
void keyPressed(unsigned char, int, int);

float ranNum;				// random number set in randomNumGen()
bool ortho = false;			// check if in orthographic or perspective view
float scale = 80.f;			// global object scale
int view = 2;				// default block view
int treeItr = 0;			// tree iterator: used to instantiate tree objects

TextureManager textureManager;

const int windmills = 1;	// number of windmills in scene - necessary to loop all windmills to setRotors()

static Windmill* windmill[windmills];
static Tree* tree[100];
static Sign* sign[1];
static House* house[10];

#endif
