#include "Stage.h"

Stage::Stage()
{
}

void Stage::display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Position objects in world space
	glTranslatef(pos[0], pos[1], pos[2]);               // Position
	glScalef(scale[0], scale[1], scale[2]);             // Scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

	drawStage();

	glPopAttrib();
	glPopMatrix();
}

void Stage::drawStage()
{
	// NEAR SIDE
	glColor3f(0.9f, 1.0f, 0.9f); // green
	glBegin(GL_QUADS);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glVertex3f(-1.f, 0.f, 1.f);
	glEnd();
	// FAR SIDE
	glColor3f(0.9f, 1.0f, 1.0f); // cyan
	glBegin(GL_QUADS);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glVertex3f(1.f, 0.f, -1.f);
	glEnd();
	// BOTTOM SIDE
	glColor3f(1.0f, 1.0f, 0.9f); // yellow
	glBegin(GL_QUADS);
	glVertex3f(-1.f, 0.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glVertex3f(1.f, 0.f, -1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();
	// TOP SIDE
	glColor3f(1.0f, 0.9f, 0.9f); // red
	glBegin(GL_QUADS);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glEnd();
	// LEFT SIDE
	glColor3f(0.9f, 0.9f, 1.0f); // blue
	glBegin(GL_QUADS);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(-1.f, 0.f, 1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();
	// RIGHT SIDE
	glColor3f(1.0f, 0.9f, 1.0f); // magenta
	glBegin(GL_QUADS);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(1.f, 0.f, -1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glEnd();
}
