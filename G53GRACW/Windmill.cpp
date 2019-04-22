#include "Windmill.h"

Windmill::Windmill() :
	animationTime(2.f)
{
}

void Windmill::update(float dT)
{
	aT = fmod(aT + dT, animationTime);
	
}

// define display function (to be called by MyScene)
void Windmill::display()
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

void Windmill::drawWindmill()
{
	float radius = 2.f;

	glTranslatef(0.f, 0.f, 0.f);                            // move draw position
	glPushMatrix();                                         // save state
	{
		drawBase(radius);											// draw base
		glPushMatrix();                                     // save position in centre of body
		{
			drawRoof(radius);                                          // draw the roof
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

void Windmill::drawBase(float radius)
{
	float res = 0.04f * M_PI;                // resolution (in radians: equivalent to 7.2 degrees)
	float r = radius;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = 6.5f;

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

void Windmill::drawRoof(float radius)
{
	float r = radius * 0.9975;                        // ratio of radius to height

	glColor3f(0.231f, 0.416f, 0.627f);
	glutSolidSphere(r, 50, 50);

	glTranslatef(0.f, 0.f, r);            // translate to edge of roof
}

void Windmill::drawRotors()
{
	glRotatef(90.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, -0.1f, 0.1f);

	float res = 0.04f * M_PI;                // resolution (in radians: equivalent to 7.2 degrees)
	float r = 0.1f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = 0.5f;

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		glColor3f(0.412f, 0.412f, 0.412f);
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

	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, 0.f, h);

	glPushMatrix();
	{
		drawRotor();
	}
	glPopMatrix();
	glRotatef(-90.f, 0.f, 0.f, 1.f);
	glPushMatrix();
	{
		drawRotor();
	}
	glPopMatrix();
	glRotatef(-90.f, 0.f, 0.f, 1.f);
	glPushMatrix();
	{
		drawRotor();
	}
	glPopMatrix();
	glRotatef(-90.f, 0.f, 0.f, 1.f);
	glPushMatrix();
	{
		drawRotor();
	}
	glPopMatrix();
}

void Windmill::drawRotor()
{
	float length = 3.f;
	float width = 0.75f;
	float thickness = -0.1f;
	float d = 0.f;

	glBegin(GL_POLYGON);
	glColor3f(0.396f, 0.263f, 0.129f);
	glVertex3f(d, d, d);
	// Front
	glVertex3f(d, length, d);
	glVertex3f(-width, length, d);
	glVertex3f(-width, length / 3, d);
	glVertex3f(-width / 5, length / 3, d);
	glVertex3f(-width / 5, d, d);
	glVertex3f(d, d, d);

	// Long Side
	glVertex3f(d, d, -thickness);
	glVertex3f(d, length, -thickness);
	glVertex3f(d, length, d);
	glVertex3f(d, d, d);

	// Bottom
	glVertex3f(-width / 5, d, d);
	glVertex3f(-width / 5, d, -thickness);
	glVertex3f(d, d, -thickness);
	glVertex3f(d, d, d);

	// Back
	glVertex3f(d, d, -thickness);
	glVertex3f(d, length, -thickness);
	glVertex3f(-width, length, -thickness);
	glVertex3f(-width, length / 3, -thickness);
	glVertex3f(-width / 5, length / 3, -thickness);
	glVertex3f(-width / 5, d, -thickness);
	glVertex3f(d, d, -thickness);

	// Top
	glVertex3f(d, length, -thickness);
	glVertex3f(-width, length, -thickness);
	glVertex3f(-width, length, d);
	glVertex3f(d, length, d);
	glVertex3f(d, length, -thickness);

	// Messy side
	glVertex3f(-width, length, -thickness);
	glVertex3f(-width, length / 3, -thickness);
	glVertex3f(-width, length / 3, d);
	glVertex3f(-width, length, d);
	glVertex3f(-width, length, -thickness);

	glVertex3f(-width, length / 3, -thickness);
	glVertex3f(-width / 5, length / 3, -thickness);
	glVertex3f(-width / 5, length / 3, d);
	glVertex3f(-width, length / 3, d);
	glVertex3f(-width, length / 3, -thickness);

	glVertex3f(-width / 5, length / 3, -thickness);
	glVertex3f(-width / 5, d, -thickness);
	glVertex3f(-width / 5, d, d);
	glVertex3f(-width / 5, length / 3, d);
	glVertex3f(-width / 5, length / 3, -thickness);

	glVertex3f(-width / 5, d, -thickness);
	glVertex3f(-width / 5, d, d);

	glEnd();
}
