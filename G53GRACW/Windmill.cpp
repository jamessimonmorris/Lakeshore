#include "Windmill.h"

Windmill::Windmill() :
	animationTime(0.67f),
	angle(0.f)
{
}

void Windmill::update(float dT)
{
	aT = fmod(aT + dT, animationTime);
	float aS = 18.f * aT / animationTime;

	if (aS < 1.f)
	{
		angle = 0.f;
	}
	else if (aS < 2.f)
	{
		angle = 5.f;
	}
	else if (aS < 3.f)
	{
		angle = 10.f;
	}
	else if (aS < 4.f)
	{
		angle = 15.f;
	}
	else if (aS < 5.f)
	{
		angle = 20.f;
	}
	else if (aS < 6.f)
	{
		angle = 25.f;
	}
	else if (aS < 7.f)
	{
		angle = 30.f;
	}
	else if (aS < 8.f)
	{
		angle = 35.f;
	}
	else if (aS < 9.f)
	{
		angle = 40.f;
	}
	else if (aS < 10.f)
	{
		angle = 45.f;
	}
	else if (aS < 11.f)
	{
		angle = 50.f;
	}
	else if (aS < 12.f)
	{
		angle = 55.f;
	}
	else if (aS < 13.f)
	{
		angle = 60.f;
	}
	else if (aS < 14.f)
	{
		angle = 65.f;
	}
	else if (aS < 15.f)
	{
		angle = 70.f;
	}
	else if (aS < 16.f)
	{
		angle = 75.f;
	}
	else if (aS < 17.f)
	{
		angle = 80.f;
	}
	else
	{
		angle = 85.f;
	}

	angle = -angle;
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
				glRotatef(angle, 0.f, 0.f, 1.f);
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
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.796f, 0.255f, 0.329f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.796f, 0.255f, 0.329f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		glColor3f(0.796f, 0.255f, 0.329f);
		// Create first points (with normals)
		glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
		glVertex3f(x, 0.f, z);          // bottom
		glVertex3f(x, h, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad (with new vertex normals)
		glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
		glVertex3f(x, h, z);          // top
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, h, 0.f);            // translate to top of branch
	glPopAttrib();
}

void Windmill::drawRoof(float radius)
{
	float r = radius * 0.99;                        // ratio of radius to height

	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.231f, 0.416f, 0.627f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.231f, 0.416f, 0.627f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	glColor3f(0.231f, 0.416f, 0.627f);
	glutSolidSphere(r, 50, 50);

	glTranslatef(0.f, 0.f, r);            // translate to edge of roof
	glPopAttrib();
}

void Windmill::drawRotors()
{
	glRotatef(90.f, 1.f, 0.f, 0.f);

	float res = 0.04f * M_PI;                // resolution (in radians: equivalent to 7.2 degrees)
	float r = 0.1f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = 0.5f;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.412f, 0.412f, 0.412f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.412f, 0.412f, 0.412f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	glPushMatrix();
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
	glPopMatrix();

	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, 0.f, h);

	glutSolidSphere(0.17, 20, 20);
	glPopAttrib();

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
	//float length = 3.f;
	//float width = 0.75f;
	//float thickness = -0.1f;

	float length = 4.f;
	float width = 1.f;
	float thickness = 0.25f;
	float z = 0.f;
	float p = 1.f;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.925f, 0.925f, 0.925f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.925f, 0.925f, 0.925f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	glBegin(GL_POLYGON);
	//glColor3f(0.396f, 0.263f, 0.129f);
	glColor3f(0.925f, 0.925f, 0.925f);
	// Front
	glNormal3f(z, z, p);
	glVertex3f(z, length, z);
	glVertex3f(-width, length, z);
	glVertex3f(-width, length / 3, z);
	glVertex3f(-width / 5, length / 3, z);
	glVertex3f(-width / 5, z, z);
	glVertex3f(z, z, z);
	glEnd();

	// Long Side
	glBegin(GL_POLYGON);
	glNormal3f(p, z, z);
	glVertex3f(z, z, -thickness);
	glVertex3f(z, length, -thickness);
	glVertex3f(z, length, z);
	glVertex3f(z, z, z);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	glNormal3f(z, -p, z);
	glVertex3f(-width / 5, z, z);
	glVertex3f(-width / 5, z, -thickness);
	glVertex3f(z, z, -thickness);
	glVertex3f(z, z, z);
	glEnd();

	// Back
	glBegin(GL_POLYGON);
	glNormal3f(z, z, -p);
	glVertex3f(z, length, -thickness);
	glVertex3f(z, z, -thickness);
	glVertex3f(-width / 5, z, -thickness);
	glVertex3f(-width / 5, length / 3, -thickness);
	glVertex3f(-width, length / 3, -thickness);
	glVertex3f(-width, length, -thickness);
	glEnd();

	// Top
	glBegin(GL_POLYGON);
	glNormal3f(z, p, z);
	glVertex3f(z, length, -thickness);
	glVertex3f(-width, length, -thickness);
	glVertex3f(-width, length, z);
	glVertex3f(z, length, z);
	glEnd();

	// Messy side
	glBegin(GL_POLYGON);
	glNormal3f(-p, z, z);
	glVertex3f(-width, length, -thickness);
	glVertex3f(-width, length / 3, -thickness);
	glVertex3f(-width, length / 3, z);
	glVertex3f(-width, length, z);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(z, -p, z);
	glVertex3f(-width, length / 3, -thickness);
	glVertex3f(-width / 5, length / 3, -thickness);
	glVertex3f(-width / 5, length / 3, z);
	glVertex3f(-width, length / 3, z);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-p, z, z);
	glVertex3f(-width / 5, length / 3, -thickness);
	glVertex3f(-width / 5, z, -thickness);
	glVertex3f(-width / 5, z, z);
	glVertex3f(-width / 5, length / 3, z);
	glEnd();

	glPopAttrib();
}
