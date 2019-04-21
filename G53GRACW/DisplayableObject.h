#ifndef ___DisplayableObject__
#define ___DisplayableObject__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class DisplayableObject
{
public:
	DisplayableObject()
	{                            // initialise world space properties
		position(0.f, 0.f, 0.f);
		size(1.f);
		orientation(0.f, 0.f, 0.f);
	}
	~DisplayableObject() { }
	virtual void display() = 0;                     // display function (MUST OVERLOAD)
	void position(float x, float y, float z)
	{       // set World Space position
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	void size(float s) { size(s, s, s); }            // set size in World Space (single value)
	void size(float sx, float sy, float sz)
	{        // set size in World Space (separate axes)
		scale[0] = sx;
		scale[1] = sy;
		scale[2] = sz;
	}
	void orientation(float rx, float ry, float rz)
	{ // set orientation in World Space
		rotation[0] = rx;
		rotation[1] = ry;
		rotation[2] = rz;
	}
	float* size() { return scale; }                  // get size in World Space 
	float* orientation() { return rotation; }        // get orientation in World Space
	float* position() { return pos; }                // get World Space position
protected:
	float pos[3];               // Position in World Space
	float scale[3];             // Size in World Space
	float rotation[3];          // Orientation in World Space
};
#endif
