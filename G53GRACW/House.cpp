#include "House.h"

House::House(int _ranNum, GLuint _texidR, GLuint _texid1, GLuint _texid2, GLuint _texid3, GLuint _texid4) :
	ranNum(_ranNum)
{
	texidR = _texidR;
	if (texidR != NULL) toTextureR = true;

	texid1 = _texid1;
	if (texid1 != NULL) toTexture1 = true;

	texid2 = _texid2;
	if (texid2 != NULL) toTexture2 = true;

	texid3 = _texid3;
	if (texid3 != NULL) toTexture3 = true;

	texid4 = _texid4;
	if (texid4 != NULL) toTexture4 = true;
}

House::House(int _ranNum) :
	ranNum(_ranNum)
{
}

House::~House()
{
}

void House::display()
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

		switch (ranNum % 4)
		{
		case 0:
			choice = 1;
			sequence = "[wwww>www>ww>w<ww>ww][^1]";
			break;
		case 1:
			choice = 2;
			sequence = "[wwww>ww>ww<w>w>w<w>ww][^2]";
			break;
		case 2:
			choice = 3;
			sequence = "[wwww>ww>ww<w>ww>www][^3]";
			break;
		case 3:
			choice = 4;
			sequence = "[wwww>www>wwww>www][^4]";
			break;
		}

		for (unsigned int i = 0; i < sequence.size(); i++)
		{
			curr = sequence[i];
			switch (curr)
			{
			case 'w':
				drawWall();
				break;
			case '1':
			case '2':
			case '3':
			case '4':
				drawRoof();
				break;
			case '<':
				glRotatef(90.f, 0.f, 1.f, 0.f);
				break;
			case '>':
				glRotatef(-90.f, 0.f, 1.f, 0.f);
				break;
			case '^':
				glTranslatef(0.f, 5.f, 0.f);
				break;
			case '[':
				glPushMatrix();
				break;
			case ']':
				glPopMatrix();
				break;
			}
		}
		glPopAttrib();
	}
	glPopMatrix();
}

void House::drawWall()
{
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.925f, 0.925f, 0.925f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 1.f, 1.f, 1.f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.1f, 0.1f, 0.1f, 1.f };               // no reflectance (black)
	float z = 0.f;
	float p = 1.f;
	float h = 5.f;							// Wall height
	float w = 4.f;							// Wall width

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	switch (choice)
	{
	case 1:
		if (toTexture1) // brick
		{
			glEnable(GL_TEXTURE_2D);                // enable texturing
			glBindTexture(GL_TEXTURE_2D, texid1);    // bind 2D texture to shape

			texCoord = 16.f;
		}
		break;
	case 2:
		if (toTexture2) // church
		{
			glEnable(GL_TEXTURE_2D);                // enable texturing
			glBindTexture(GL_TEXTURE_2D, texid2);    // bind 2D texture to shape

			texCoord = 4.f;
		}
		break;
	case 3:
		if (toTexture3) // house1
		{
			glEnable(GL_TEXTURE_2D);                // enable texturing
			glBindTexture(GL_TEXTURE_2D, texid3);    // bind 2D texture to shape

			texCoord = 4.f;
		}
		break;
	case 4:
		if (toTexture4)
		{
			glEnable(GL_TEXTURE_2D);                // enable texturing
			glBindTexture(GL_TEXTURE_2D, texid4);    // bind 2D texture to shape

			texCoord = 4.f;
		}
		break;
	}

	glDisable(GL_CULL_FACE);

	glBegin(GL_POLYGON);
	glNormal3f(z, z, -p);
	if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.f); // 16 for brick, 4 for house1
	glVertex3f(z, z, z);
	if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 1.f);
	glVertex3f(z, h, z);
	if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 1.f);
	glVertex3f(w, h, z);
	if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
	glVertex3f(w, z, z);
	glEnd();

	glEnable(GL_CULL_FACE);

	if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glTranslatef(w, z, z);
	glPopAttrib();
}

void House::drawRoof()
{
	float mat_colour[]                      // colour reflected by diffuse light
		= { 0.729f, 0.416f, 0.345f, 1.f };         // mid brown
	float mat_ambient[]                     // ambient colour
		= { 0.829f, 0.516f, 0.445f, 1.f };         // dark brown
	float mat_colour1[]                      // colour reflected by diffuse light
	= { 0.925f, 0.925f, 0.925f, 1.f };         // mid brown
	float mat_ambient1[]                     // ambient colour
		= { 1.f, 1.f, 1.f, 1.f };         // dark brown
	float mat_spec[]                        // specular colour
		= { 0.1f, 0.1f, 0.1f, 1.f };               // no reflectance (black)
	float z = 0.f;
	float p = 1.f;
	float h = 2.5f;							// Roof height
	float g = 0.5f;							// Roof gap

	glPushAttrib(GL_ALL_ATTRIB_BITS);       // save current style attributes (inc. material properties)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient); // set colour for ambient reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);  // set colour for diffuse reflectance
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

	if (toTextureR)
	{
		glEnable(GL_TEXTURE_2D);                // enable texturing
		glBindTexture(GL_TEXTURE_2D, texidR);    // bind 2D texture to shape
	}

	glDisable(GL_CULL_FACE);

	glTranslatef(-g, -0.25f, -g);

	glBegin(GL_POLYGON);

	switch (choice)
	{
	case 1:
		glNormal3f(z, p, -h);
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(z, z, z);
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(z, h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f + (2 * g), z, z);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, p, h);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(16.f + (2 * g), z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(z, h, 4.f + g);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(-h, p, z);
		if (toTextureR) glTexCoord2f(0.529f, 0.f);
		glVertex3f(8.f, z, 8.f + g);
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(8.f, z, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(12.f + g, h, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(12.f + g, h, 4.f + g);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(h, p, z);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f + (2 * g), z, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(0.471f, 0.f);
		glVertex3f(16.f + (2 * g), z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(12.f + g, h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(12.f + g, h, 12.f + (2 * g));
		glEnd();
		if (toTextureR) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

		glTranslatef(g, 0.25f, g);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1); // set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour1);  // set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

		switch (choice)
		{
		case 1:
			if (toTexture1)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid1);    // bind 2D texture to shape
			}
			break;
		case 2:
			if (toTexture2)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid2);    // bind 2D texture to shape
			}
			break;
		case 3:
			if (toTexture3)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid3);    // bind 2D texture to shape
			}
			break;
		case 4:
			if (toTexture4)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid4);    // bind 2D texture to shape
			}
			break;
		}

		glBegin(GL_POLYGON);
		glNormal3f(-p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(z, z, 8.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(z, h - 0.25f, 4.f);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, z, p);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(8.f, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(16.f, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(12.f, h - 0.25f, 12.f);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f, z, 8.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(16.f, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(16.f, h - 0.25f, 4.f);
		break;
	case 2:
		glNormal3f(z, p, -h);
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(z, z, z);
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(z, h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f + (2 * g), z, z);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, p, h);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(16.f + (2 * g), z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(z, h, 4.f + g);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(-h, p, z);
		if (toTextureR) glTexCoord2f(0.529f, 0.f);
		glVertex3f(4.f + (g / 2), z, 8.f + g);
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(4.f + (g / 2), z, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(6.f + g, h, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(6.f + g, h, 4.f + g);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(h, p, z);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(8.f + (1.5 * g), z, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(0.471f, 0.f);
		glVertex3f(8.f + (1.5 * g), z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(6.f + g, h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(6.f + g, h, 12.f + (2 * g));
		glEnd();
		if (toTextureR) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

		glTranslatef(g, 0.25f, g);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1); // set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour1);  // set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

		switch (choice)
		{
		case 1:
			if (toTexture1)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid1);    // bind 2D texture to shape
			}
			break;
		case 2:
			if (toTexture2)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid2);    // bind 2D texture to shape
			}
			break;
		case 3:
			if (toTexture3)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid3);    // bind 2D texture to shape
			}
			break;
		case 4:
			if (toTexture4)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid4);    // bind 2D texture to shape
			}
			break;
		}

		glBegin(GL_POLYGON);
		glNormal3f(-p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(z, z, 8.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(z, h - 0.25f, 4.f);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, z, p);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(4.f, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.f);
		glVertex3f(8.f, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord / 2, 0.5f);
		glVertex3f(6.f, h - 0.25f, 12.f);
		glEnd();

		glPushMatrix();
		{
			glBegin(GL_POLYGON);
			glVertex3f(5.9f, h - 2.2f, 12.05f);
			glVertex3f(6.1f, h - 2.2f, 12.05f);
			glVertex3f(6.1f, h - 1.1f, 12.05f);
			glVertex3f(5.9f, h - 1.1f, 12.05f);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(5.6f, h - 1.6f, 12.05f);
			glVertex3f(6.4f, h - 1.6f, 12.05f);
			glVertex3f(6.4f, h - 1.4f, 12.05f);
			glVertex3f(5.6f, h - 1.4f, 12.05f);
			glEnd();
		}
		glPopMatrix();

		glBegin(GL_POLYGON);
		glNormal3f(p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f, z, 8.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(16.f, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(16.f, h - 0.25f, 4.f);
		break;
	case 3:
		glNormal3f(z, p, -h);
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(z, z, z);
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(z, h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f + (2 * g), z, z);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, p, h);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(16.f + (2 * g), z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(z, h, 4.f + g);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(-h, p, z);
		if (toTextureR) glTexCoord2f(0.529f, 0.f);
		glVertex3f(z, z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(z, z, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(4.f + g, h, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(4.f + g, h, 4.f + g);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(h, p, z);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(8.f + (2 * g), z, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(0.471f, 0.f);
		glVertex3f(8.f + (2 * g), z, 8.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(4.f + g, h, 4.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(4.f + g, h, 12.f + (2 * g));
		glEnd();
		if (toTextureR) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

		glTranslatef(g, 0.25f, g);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1); // set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour1);  // set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

		switch (choice)
		{
		case 1:
			if (toTexture1)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid1);    // bind 2D texture to shape
			}
			break;
		case 2:
			if (toTexture2)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid2);    // bind 2D texture to shape
			}
			break;
		case 3:
			if (toTexture3)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid3);    // bind 2D texture to shape
			}
			break;
		case 4:
			if (toTexture4)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid4);    // bind 2D texture to shape
			}
			break;
		}

		glBegin(GL_POLYGON);
		glNormal3f(-p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(z, z, 8.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(z, h - 0.25f, 4.f);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, z, p);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(8.f, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(4.f, h - 0.25f, 12.f);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f, z, 8.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(2 * texCoord, 0.f);
		glVertex3f(16.f, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(texCoord, 0.5f);
		glVertex3f(16.f, h - 0.25f, 4.f);
		break;
	case 4:
		glNormal3f(z, p, -h);
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(z, 0.075f, z);
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(z, h, 6.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 6.f + g);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f + (2 * g), 0.075f, z);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(z, p, h);
		if (toTextureR) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, 0.075f, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 0.f);
		glVertex3f(16.f + (2 * g), 0.075f, 12.f + (2 * g));
		if (toTextureR) glTexCoord2f(1.f, 1.f);
		glVertex3f(16.f + (2 * g), h, 6.f + g);
		if (toTextureR) glTexCoord2f(0.f, 1.f);
		glVertex3f(z, h, 6.f + g);
		glEnd();
		if (toTextureR) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

		glTranslatef(g, 0.25f, g);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient1); // set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour1);  // set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);   // set colour for specular reflectance

		switch (choice)
		{
		case 1:
			if (toTexture1)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid1);    // bind 2D texture to shape
			}
			break;
		case 2:
			if (toTexture2)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid2);    // bind 2D texture to shape
			}
			break;
		case 3:
			if (toTexture3)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid3);    // bind 2D texture to shape
			}
			break;
		case 4:
			if (toTexture4)
			{
				glEnable(GL_TEXTURE_2D);                // enable texturing
				glBindTexture(GL_TEXTURE_2D, texid4);    // bind 2D texture to shape
			}
			break;
		}

		glBegin(GL_POLYGON);
		glNormal3f(-p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(z, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(3 * texCoord, 0.f);
		glVertex3f(z, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(1.5 * texCoord, 0.5f);
		glVertex3f(z, h - 0.25f, 6.f);
		glEnd();
		glBegin(GL_POLYGON);
		glNormal3f(p, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(0.f, 0.f);
		glVertex3f(16.f, z, 12.f);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(3 * texCoord, 0.f);
		glVertex3f(16.f, z, z);
		if (toTexture1 || toTexture2 || toTexture3 || toTexture4) glTexCoord2f(1.5 * texCoord, 0.5f);
		glVertex3f(16.f, h - 0.25f, 6.f);
		break;
	}

	glEnd();

	glEnable(GL_CULL_FACE);

	if (toTextureR) glDisable(GL_TEXTURE_2D);    // disable texturing following this point

	glPopAttrib();
}
