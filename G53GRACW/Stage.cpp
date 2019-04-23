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
	float mat_colour1[]                      // colour reflected by diffuse light
		= { 0.9f, 1.0f, 0.9f, 1.f };         // mid brown
	float mat_ambient1[]                     // ambient colour
		= { 0.9f, 1.0f, 0.9f, 1.f };         // dark brown
	float mat_spec1[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour1);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec1);   // set colour for specular reflectance
	glColor3f(0.9f, 1.0f, 0.9f); // green

	glBegin(GL_QUADS);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glVertex3f(-1.f, 0.f, 1.f);
	glEnd();
	// FAR SIDE
	float mat_colour2[]                      // colour reflected by diffuse light
		= { 0.9f, 1.0f, 1.0f, 1.f };         // mid brown
	float mat_ambient2[]                     // ambient colour
		= { 0.9f, 1.0f, 1.0f, 1.f };         // dark brown
	float mat_spec2[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient2); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour2);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec2);   // set colour for specular reflectance
	glColor3f(0.9f, 1.0f, 1.0f); // cyan

	glBegin(GL_QUADS);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glVertex3f(1.f, 0.f, -1.f);
	glEnd();
	// BOTTOM SIDE
	float mat_colour3[]                      // colour reflected by diffuse light
		= { 1.0f, 1.0f, 0.9f, 1.f };         // mid brown
	float mat_ambient3[]                     // ambient colour
		= { 1.0f, 1.0f, 0.9f, 1.f };         // dark brown
	float mat_spec3[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient3); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour3);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec3);   // set colour for specular reflectance
	glColor3f(1.0f, 1.0f, 0.9f); // yellow

	glBegin(GL_QUADS);
	glVertex3f(-1.f, 0.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glVertex3f(1.f, 0.f, -1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();
	// TOP SIDE
	float mat_colour4[]                      // colour reflected by diffuse light
		= { 1.0f, 0.9f, 0.9f, 1.f };         // mid brown
	float mat_ambient4[]                     // ambient colour
		= { 1.0f, 0.9f, 0.9f, 1.f };         // dark brown
	float mat_spec4[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient4); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour4);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec4);   // set colour for specular reflectance
	glColor3f(1.0f, 0.9f, 0.9f); // red

	glBegin(GL_QUADS);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glEnd();
	// LEFT SIDE
	float mat_colour5[]                      // colour reflected by diffuse light
		= { 0.9f, 0.9f, 1.0f, 1.f };         // mid brown
	float mat_ambient5[]                     // ambient colour
		= { 0.9f, 0.9f, 1.0f, 1.f };         // dark brown
	float mat_spec5[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient5); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour5);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec5);   // set colour for specular reflectance
	glColor3f(0.9f, 0.9f, 1.0f); // blue

	glBegin(GL_QUADS);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(-1.f, 0.f, 1.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();
	// RIGHT SIDE
	float mat_colour6[]                      // colour reflected by diffuse light
		= { 1.0f, 0.9f, 1.0f, 1.f };         // mid brown
	float mat_ambient6[]                     // ambient colour
		= { 1.0f, 0.9f, 1.0f, 1.f };         // dark brown
	float mat_spec6[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient6); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour6);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec6);   // set colour for specular reflectance
	glColor3f(1.0f, 0.9f, 1.0f); // magenta

	glBegin(GL_QUADS);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(1.f, 0.f, -1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glEnd();
	glPopAttrib();
}
