#include "TreeLong.h"

TreeLong::TreeLong(float randomNum, GLuint _texid) :
	ranNum(randomNum),
	height(((int)ranNum % 2) + 6)
{
	texid = _texid;
	if (texid != NULL)
		toTexture = true;
}

TreeLong::TreeLong(float randomNum) :
	ranNum(randomNum),
	height(((int)ranNum % 2) + 6)
{

}

// define display function (to be called by MyScene)
void TreeLong::display()
{
	glPushMatrix();
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glTranslatef(pos[0], pos[1], pos[2]);               // Position
		glScalef(scale[0], scale[1], scale[2]);             // Scale
		glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
		glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
		glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

		char curr;
		string sequence;

		sequence = "[ttt[>l]]";

		for (unsigned int i = 0; i < sequence.size(); i++)
		{
			curr = sequence[i];			// for each char in sequence
			switch (curr)				// check current char command
			{
			case 't':                   // draw trunk, move forward
				glTranslatef(0.f, -0.1f, 0.f);
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

		glPopAttrib();
	}
	glPopMatrix();
}

void TreeLong::leaves()
{
	float rad = ranNum / 15;		// radius of leaves
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.133f, 0.545f, 0.133f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.033f, 0.445f, 0.033f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	glColor3f(0.133f, 0.545f, 0.133f);

	glutSolidCone(rad, height, 50, 50);

	glTranslatef(0.f, 0.f, (rad * 3) / 5);            // translate to top of branch
	glPopAttrib();
}

void TreeLong::trunk()
{
	float res = 0.1f * M_PI;                // resolution (in radians: equivalent to 18 degrees)
	float r = ranNum / 100;					// ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.545f, 0.271f, 0.075f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.445f, 0.171f, 0.f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.f, 0.f, 0.f, 1.f };               // no reflectance (black)

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	glColor3f(0.545f, 0.271f, 0.075f);         // set face colour to brown (rgb)

	if (toTexture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
	}

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		// Create first points (with normals)
		glNormal3f(x, 0.f, z);          // define a normal facing out from the centre (0,0,0)
		if (toTexture) glTexCoord2f(0.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (0,0)
		glVertex3f(x, 0.f, z);          // bottom
		if (toTexture) glTexCoord2f(0.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (0,1)
		glVertex3f(x, 0.75f, z);          // top
		// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad (with new vertex normals)
		glNormal3f(x, 0.f, z);          // define a new normal now that x,z have moved around
		if (toTexture) glTexCoord2f(1.f, 1.f);  // assign texture coordinates to next vertex (u,v) = (1,1)
		glVertex3f(x, 0.75f, z);          // top
		if (toTexture) glTexCoord2f(1.f, 0.f);  // assign texture coordinates to next vertex (u,v) = (1,0)
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	if (toTexture) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glTranslatef(0.f, 0.75f, 0.f);            // translate to top of trunk
	glPopAttrib();
}
