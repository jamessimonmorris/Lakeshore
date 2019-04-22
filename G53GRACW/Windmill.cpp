#include "Windmill.h"

Windmill::Windmill() :
	animationTime(6.f)
{
}

void Windmill::update(float dT)
{

}

// define display function (to be called by MyScene)
void Windmill::display()
{
	glPushMatrix();
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glTranslatef(pos[0], pos[1], pos[2]);               // Position
		glScalef(scale[0], scale[1], scale[2]);             // Scale
		glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
		glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
		glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

		drawWindmill();

		glPopAttrib();
	}
	glPopMatrix();
}

void Windmill::drawWindmill()
{
	glTranslatef(-5.f, 0.f, 0.f);                            // move draw position
	glPushMatrix();                                         // save state
	{
		drawBase();											// draw base
		glPushMatrix();                                     // save position in centre of body
		{
			drawRoof();                                          // draw the roof
			glPushMatrix();
			{
				drawRotors();
			}
			glPopMatrix();
		}
		glPopMatrix();                                      // pop back to central point
	}
	glPopMatrix();                                          // restore state

}

void Windmill::drawBase()
{
	float res = 0.04f * M_PI;                // resolution (in radians: equivalent to 7.2 degrees)
	float r = 2.5f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = 5.f;

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		glColor3f(0.796f, 0.255f, 0.329f);
		// Create first points
		glVertex3f(x, 0.f, z);          // bottom
		glVertex3f(x, h, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		glVertex3f(x, h, z);          // top
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, h, 0.f);            // translate to top of branch
}

void Windmill::drawRoof()
{
	float r = 2.495f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = 5.f;

	glColor3f(0.231f, 0.416f, 0.627f);
	glutSolidSphere(r, 50, 50);

	glTranslatef(0.f, 0.f, r);            // translate to top of branch
}

void Windmill::drawRotors()
{
}
