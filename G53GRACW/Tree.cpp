#include "Tree.h"

Tree::Tree()
{
	srand(time(NULL));
	ranNum = (float) (rand() % 21) + 30;
}

// define display function (to be called by MyScene)
void Tree::display()
{
	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);			// Position
	glScalef(scale[0], scale[1], scale[2]);			// Scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);			// Set orientation (Y - roll)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);			// Set orientation (Z - yaw)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);			// Set orientation (X - pitch)

	char curr;
	string sequence = "[tt[>lll]]";

	for (unsigned int i = 0; i < sequence.size(); i++)
	{
		curr = sequence[i];			// for each char in sequence
		switch (curr)				// check current char command
		{                 
		case 't':                   // draw trunk, move forward
			glScalef(0.95f, 0.95f, 0.95f);
			trunk();
			break;
		case 'l':                   // leaves
			glScalef(0.85f, 0.85f, 0.85f);
			leaves();
			break;
		case '[':					// Save
			glPushMatrix();
			break;
		case ']':					// Restore
			glPopMatrix();
			break;
		case '>':
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			break;
		}
	}
}

void Tree::leaves()
{
	float rad = ranNum / 15;		// radius of leaves

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(0.133f, 0.545f, 0.133f);

	glutSolidCone(rad, (rad * 5) / 4, 50, 50);

	glTranslatef(0.f, 0.f, (rad * 3) / 5);            // translate to top of branch
	glPopAttrib();
}

void Tree::trunk()
{
	float res = 0.1f * M_PI;                // resolution (in radians: equivalent to 18 degrees)
	float r = ranNum / 100;					// ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(0.545f, 0.271f, 0.075f);

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x, 0.f, z);          // bottom
		glVertex3f(x, 0.75f, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		glVertex3f(x, 0.75f, z);          // top
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, 0.75f, 0.f);            // translate to top of branch
	glPopAttrib();
}
