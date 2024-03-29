#include "Windmill.h"

Windmill::Windmill(GLuint _texidB, GLuint _texidR, GLuint _texidW, GLuint _texidF, GLuint _texidM) :
	angle(0.f)
{
	animationTime = (float) ((360 / rotors) * speed);

	texidB = _texidB;							// Instantiate all necessary texture supporting variables
	if (texidB != NULL) toTextureB = true;

	texidR = _texidR;
	if (texidR != NULL) toTextureR = true;

	texidW = _texidW;
	if (texidW != NULL) toTextureW = true;

	texidF = _texidF;
	if (texidF != NULL) toTextureF = true;

	texidM = _texidM;
	if (texidM != NULL) toTextureM = true;
}

Windmill::Windmill() :
	angle(0.f)
{
}

void Windmill::update(float dT)
{
	// Update windmill rotation based on current number of rotors and hard-coded speed
	animationTime = (float)((360 / rotors) * speed);

	aT = fmod(aT + dT, animationTime);
	int steps = 360 / (rotors * 1);
	float aS = steps * aT / animationTime;

	angle = -floor(aS) * (360 / (rotors * steps));		// Calculate rotation angle
}

void Windmill::setRotors(int _rotors)
{
	if (_rotors > 8 || _rotors < 4) {}		// Change number of rotors
	else
		rotors = _rotors;
}

int Windmill::getRotors()
{
	return rotors;
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
	float radius = 2.f;

	glPushMatrix();                                         // save state
	{
		drawBase(radius);									// draw base
		glPushMatrix();                                     // save position in centre of body
		{
			drawRoof(radius);								// draw the roof
			glPushMatrix();
			{
				glRotatef(angle, 0.f, 0.f, 1.f);
				drawRotors();								// draw each rotor at angle proportional to current number of rotors present
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
	float h = 7.5f;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.925f, 0.925f, 0.925f, 1.f };
	float mat_ambient[]                     // ambient colour
		= { 1.f, 1.f, 1.f, 1.f };
	float mat_spec[]                        // specular colour
		= { 0.1f, 0.1f, 0.1f, 1.f };

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	if (toTextureB)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidB);    // bind 2D texture to shape
	}

	do
	{                                     // create base of windmill with multiple QUADS
		glBegin(GL_QUADS);
		glColor3f(0.796f, 0.255f, 0.329f);
		// Create first points (with normals)
		glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
		if (toTextureB) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
		glVertex3f(x, 0.f, z);          // bottom
		if (toTextureB) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
		glVertex3f(x, h, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad (with new vertex normals)
		glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
		if (toTextureB) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
		glVertex3f(x, h, z);          // top
		if (toTextureB) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	if (toTextureB) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glTranslatef(0.f, h, 0.f);            // translate to top of base walls
	glPopAttrib();
}

void Windmill::drawRoof(float radius)
{
	float r = radius * 0.99;                        // calculate radius dependent on radius of base walls

	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.729f, 0.416f, 0.345f, 1.f };
	float mat_ambient[]                     // ambient colour
		= { 0.829f, 0.516f, 0.445f, 1.f };
	float mat_spec[]                        // specular colour
		= { 0.2f, 0.2f, 0.2f, 1.f };

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	if (toTextureR)
	{
		glEnable(GL_TEXTURE_2D);					// enable texturing
		GLUquadric* quadratic = gluNewQuadric();	// Create sphere with texturing
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, texidR);
		gluSphere(quadratic, r, 50, 50);
	}
	else
	{
		gluSphere(gluNewQuadric(), r, 50, 50);
	}

	if (toTextureR) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glTranslatef(0.f, 0.f, r);            // translate to edge of roof
	glPopAttrib();
}

void Windmill::drawRotors()
{
	glRotatef(90.f, 1.f, 0.f, 0.f);

	float res = 0.1f * M_PI;                // resolution (in radians: equivalent to 18 degrees)
	float r = 0.1f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float h = 0.5f;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.412f, 0.412f, 0.412f, 1.f };
	float mat_ambient[]                     // ambient colour
		= { 0.512f, 0.512f, 0.512f, 1.f };
	float mat_spec[]                        // specular colour
		= { 0.15f, 0.15f, 0.15f, 1.f };

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	glPushMatrix();
	glTranslatef(0.f, -0.1f, 0.f);

	if (toTextureM)
	{
		glEnable(GL_TEXTURE_2D);			// enable textures
		glBindTexture(GL_TEXTURE_2D, texidM);
	}

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		glColor3f(0.412f, 0.412f, 0.412f);
		// Create first points
		if (toTextureM) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
		glVertex3f(x, 0.f, z);          // bottom
		if (toTextureM) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
		glVertex3f(x, h, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		if (toTextureM) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
		glVertex3f(x, h, z);          // top
		if (toTextureM) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	if (toTextureM) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glPopMatrix();

	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, 0.f, h);

	if (toTextureM)
	{
		glEnable(GL_TEXTURE_2D);					// enable texturing
		GLUquadric* quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);	// create sphere with textures
		gluQuadricTexture(quadratic, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, texidM);
		gluSphere(quadratic, 0.15, 20, 20);
	}
	else
	{
		gluSphere(gluNewQuadric(), 0.15, 20, 20);
	}

	if (toTextureM) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glPopAttrib();

	for (int i = rotors; i > 0; i--)		// create number of rotors specified
	{
		glPushMatrix();
		{
			drawRotor();
		}
		glPopMatrix();
		glRotatef(-(360.f / rotors), 0.f, 0.f, 1.f);
	}

	glRotatef(360.f / rotors, 0.f, 0.f, 1.f);
}

void Windmill::drawRotor()
{
	float length = 4.f;
	float width = 1.f;
	float thickness = 0.15f;
	float z = 0.f;
	float p = 1.f;
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.925f, 0.925f, 0.925f, 1.f };
	float mat_ambient[]                     // ambient colour
		= { 1.f, 1.f, 1.f, 1.f };
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	// Front wood
	if (toTextureW)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidW);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, z, p);
	if (toTextureW) glTexCoord2f(0.f, 0.f);	// assign texture coordinates to next vertex (u,v) = (0,0)
	glVertex3f(-width / 5, z, z);
	if (toTextureW) glTexCoord2f(1.f, 0.f);	// assign texture coordinates to next vertex (u,v) = (1,0)
	glVertex3f(z, z, z);
	if (toTextureW) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(z, length, z);
	if (toTextureW) glTexCoord2f(0.f, 1.f);	// assign texture coordinates to next vertex (u,v) = (0,1)
	glVertex3f(-width / 5, length, z);
	glEnd();
	if (toTextureW) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Front fabric
	if (toTextureF)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidF);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, z, p);
	if (toTextureF) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
	glVertex3f(-width, length / 3, -thickness / 3);
	if (toTextureF) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
	glVertex3f(-width / 5, length / 3, -thickness / 3);
	if (toTextureF) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length - (thickness / 3), -thickness / 3);
	if (toTextureF) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
	glVertex3f(-width, length - (thickness / 3), -thickness / 3);
	glEnd();
	if (toTextureF) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Long Wood Side
	if (toTextureW)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidW);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(p, z, z);
	if (toTextureW) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
	glVertex3f(z, z, z);
	if (toTextureW) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
	glVertex3f(z, z, -thickness);
	if (toTextureW) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(z, length, -thickness);
	if (toTextureW) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
	glVertex3f(z, length, z);
	glEnd();
	if (toTextureW) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Bottom
	glBegin(GL_POLYGON);
	glNormal3f(z, -p, z);
	glVertex3f(-width / 5, z, z);
	glVertex3f(-width / 5, z, -thickness);
	glVertex3f(z, z, -thickness);
	glVertex3f(z, z, z);
	glEnd();

	// Back wood
	if (toTextureW)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidW);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, z, -p);
	if (toTextureW) glTexCoord2f(0.f, 0.f);	// assign texture coordinates to next vertex (u,v) = (0,0)
	glVertex3f(z, z, -thickness);
	if (toTextureW) glTexCoord2f(1.f, 0.f);	// assign texture coordinates to next vertex (u,v) = (1,0)
	glVertex3f(-width / 5, z, -thickness);
	if (toTextureW) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length, -thickness);
	if (toTextureW) glTexCoord2f(0.f, 1.f);	// assign texture coordinates to next vertex (u,v) = (0,1)
	glVertex3f(z, length, -thickness);
	glEnd();
	if (toTextureW) glDisable(GL_TEXTURE_2D);    // disable texturing following this point
	
	// Back fabric
	if (toTextureF)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidF);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, z, -p);
	if (toTextureF) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
	glVertex3f(-width / 5, length / 3, -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
	glVertex3f(-width, length / 3, -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length - (thickness / 3), -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
	glVertex3f(-width / 5, length - (thickness / 3), -(2 * thickness) / 3);
	glEnd();
	if (toTextureF) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Top Wood
	if (toTextureW)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidW);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, p, z);
	if (toTextureW) glTexCoord2f(0.f, 0.954f);  // assign texture coordinates to next vertex (u,v) = (0,0.954)
	glVertex3f(-width / 5, length, z);
	if (toTextureW) glTexCoord2f(1.f, 0.954f);  // assign texture coordinates to next vertex (u,v) = (1,0.954)
	glVertex3f(z, length, z);
	if (toTextureW) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(z, length, -thickness);
	if (toTextureW) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
	glVertex3f(-width / 5, length, -thickness);
	glEnd();
	if (toTextureW) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Top fabric
	if (toTextureF)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidF);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, p, z);
	if (toTextureF) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length - (thickness / 3), -thickness / 3);
	if (toTextureF) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length - (thickness / 3), -thickness / 3);
	if (toTextureF) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length - (thickness / 3), -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length - (thickness / 3), -(2 * thickness) / 3);
	glEnd();
	if (toTextureF) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Fabric side
	if (toTextureF)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidF);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(-p, z, z);
	if (toTextureF) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length / 3, -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length / 3, -thickness / 3);
	if (toTextureF) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length - (thickness / 3), -thickness / 3);
	if (toTextureF) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length - (thickness / 3), -(2 * thickness) / 3);
	glEnd();
	if (toTextureF) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Bottom fabric
	if (toTextureF)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidF);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(z, -p, z);
	if (toTextureF) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length / 3, -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length / 3, -(2 * thickness) / 3);
	if (toTextureF) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length / 3, -thickness / 3);
	if (toTextureF) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width, length / 3, -thickness / 3);
	glEnd();
	if (toTextureF) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	// Inside wood
	if (toTextureW)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidW);    // bind 2D texture to shape
	}
	glBegin(GL_POLYGON);
	glNormal3f(-p, z, z);
	if (toTextureW) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, z, -thickness);
	if (toTextureW) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, z, z);
	if (toTextureW) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length, z);
	if (toTextureW) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
	glVertex3f(-width / 5, length, -thickness);
	glEnd();
	if (toTextureW) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glPopAttrib();
}
