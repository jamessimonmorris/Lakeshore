#include "Sign.h"

Sign::Sign(GLuint _texidP, GLuint _texidS, GLuint _texidB)
{
	texidP = _texidP;
	if (texidP != NULL) toTextureP = true;

	texidS = _texidS;
	if (texidS != NULL) toTextureS = true;

	texidB = _texidB;
	if (texidB != NULL) toTextureB = true;
}

Sign::Sign()
{
}

Sign::~Sign()
{
}

void Sign::display()
{
	glPushMatrix();
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glTranslatef(pos[0], pos[1], pos[2]);               // Position
		glScalef(scale[0], scale[1], scale[2]);             // Scale
		glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
		glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
		glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

		drawSign();

		glPopAttrib();
	}
	glPopMatrix();
}

void Sign::drawSign()
{
	float postRadius = 0.25f;
	float postHeight = 6.f;
	float signWidth = 10.f;
	float signHeight = 5.f;
	float signThickness = 0.1f;

	drawPost(postRadius, postHeight);
	glTranslatef(signWidth * 0.85f, -postHeight, 0.f);
	drawPost(postRadius, postHeight);

	glPushMatrix();
	{
		glRotatef(2.f, 0.f, 0.f, 1.f);
		glTranslatef(signWidth * 0.065f, signHeight * 0.25f, postRadius);
		drawBoard(signWidth, signHeight, signThickness);
	}
	glPopMatrix();
}

void Sign::drawPost(float _radius, float _height)
{
	float res = 0.1f * M_PI;                // resolution (in radians: equivalent to 18 degrees)
	float r = _radius;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = _height;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.412f, 0.412f, 0.412f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.512f, 0.512f, 0.512f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.1f, 0.1f, 0.1f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	if (toTextureP)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidP);    // bind 2D texture to shape
	}

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		glColor3f(0.796f, 0.255f, 0.329f);
		// Create first points (with normals)
		glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
		if (toTextureP) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
		glVertex3f(x, 0.f, z);          // bottom
		if (toTextureP) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
		glVertex3f(x, h, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad (with new vertex normals)
		glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
		if (toTextureP) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
		glVertex3f(x, h, z);          // top
		if (toTextureP) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	if (toTextureP) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glTranslatef(0.f, h, 0.f);            // translate to top of branch

	if (toTextureP)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		GLUquadric* quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, texidP);
		gluSphere(quadratic, r, 20, 20);
	}
	else
	{
		gluSphere(gluNewQuadric(), r, 20, 20);
	}

	if (toTextureP) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glPopAttrib();
}

void Sign::drawBoard(float width, float height, float thickness)
{
	float z = 0.f;
	float p = 1.f;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.925f, 0.925f, 0.925f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 1.f, 1.f, 1.f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	// Front
	if (toTextureS)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidS);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, z, p);
	if (toTextureS) glTexCoord2f(0.f, 0.f);
	glVertex3f(-width, -height, thickness);
	if (toTextureS) glTexCoord2f(1.f, 0.f);
	glVertex3f(z, -height, thickness);
	if (toTextureS) glTexCoord2f(1.f, 1.f);
	glVertex3f(z, z, thickness);
	if (toTextureS) glTexCoord2f(0.f, 1.f);
	glVertex3f(-width, z, thickness);
	glEnd();
	if (toTextureS) glDisable(GL_TEXTURE_2D);

	// Back
	if (toTextureB)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidB);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, z, -p);
	if (toTextureB) glTexCoord2f(0.f, 0.f);
	glVertex3f(z, -height, z);
	if (toTextureB) glTexCoord2f(1.f, 0.f);
	glVertex3f(-width, -height, z);
	if (toTextureB) glTexCoord2f(1.f, 1.f);
	glVertex3f(-width, z, z);
	if (toTextureB) glTexCoord2f(0.f, 1.f);
	glVertex3f(z, z, z);
	glEnd();
	if (toTextureB) glDisable(GL_TEXTURE_2D);

	// Right Side
	if (toTextureP)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidP);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(p, z, z);
	if (toTextureP) glTexCoord2f(0.f, 0.f);
	glVertex3f(z, -height, thickness);
	if (toTextureP) glTexCoord2f(1.f, 0.f);
	glVertex3f(z, -height, z);
	if (toTextureP) glTexCoord2f(1.f, 1.f);
	glVertex3f(z, z, z);
	if (toTextureP) glTexCoord2f(0.f, 1.f);
	glVertex3f(z, z, thickness);
	glEnd();

	// Left Side
	glBegin(GL_POLYGON);
	glNormal3f(-p, z, z);
	if (toTextureP) glTexCoord2f(0.f, 0.f);
	glVertex3f(-width, -height, z);
	if (toTextureP) glTexCoord2f(1.f, 0.f);
	glVertex3f(-width, -height, thickness);
	if (toTextureP) glTexCoord2f(1.f, 1.f);
	glVertex3f(-width, z, thickness);
	if (toTextureP) glTexCoord2f(0.f, 1.f);
	glVertex3f(-width, z, z);
	glEnd();

	// Top
	glBegin(GL_POLYGON);
	glNormal3f(z, p, z);
	if (toTextureP) glTexCoord2f(0.f, 0.f);
	glVertex3f(-width, z, thickness);
	if (toTextureP) glTexCoord2f(1.f, 0.f);
	glVertex3f(z, z, thickness);
	if (toTextureP) glTexCoord2f(1.f, 1.f);
	glVertex3f(z, z, z);
	if (toTextureP) glTexCoord2f(0.f, 1.f);
	glVertex3f(-width, z, z);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	glNormal3f(z, -p, z);
	if (toTextureS) glTexCoord2f(0.f, 0.f);
	glVertex3f(-width, -height, z);
	if (toTextureS) glTexCoord2f(1.f, 0.f);
	glVertex3f(-width, -height, thickness);
	if (toTextureS) glTexCoord2f(1.f, 1.f);
	glVertex3f(z, -height, thickness);
	if (toTextureS) glTexCoord2f(0.f, 1.f);
	glVertex3f(z, -height, z);
	glEnd();
	if (toTextureS) glDisable(GL_TEXTURE_2D);

	glPopAttrib();
}
