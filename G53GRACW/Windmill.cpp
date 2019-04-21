#include "Windmill.h"

Windmill::Windmill()
{
}

// define display function (to be called by MyScene)
void Windmill::display()
{
	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);  // set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);  // set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);  // set orientation (X)
	base();                                 // draw base
}

void Windmill::base()
{
	float res = 0.1f * M_PI;                // resolution (in radians: equivalent to 18 degrees)
	float r = 0.15f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x, 0.f, z);          // bottom
		glVertex3f(x, 1.f, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		glVertex3f(x, 1.f, z);          // top
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, 1.f, 0.f);            // translate to top of branch
}
