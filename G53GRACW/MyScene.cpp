#include "MyScene.h"

void setup()
{
	width = 1200;                                   // initialise global window variables
	height = 800;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("My Scene");                   // create and show window (named MyScene)

	Windmill *windmill;
	windmill = new Windmill();
	objects["windmill"] = windmill;
	reshape(width, height);
}

void reshape(int _width, int _height)
{
	// update global dimension variables
	width = _width;
	height = _height;
	// calculate new aspect ratio
	GLdouble aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();     // reset matrix
	gluPerspective(60.0, aspect, 1, 1000);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW); // return matrix mode to modelling and viewing
}

void draw()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.f, -4.f, -10.f);
	glColor3f(0.f, 0.f, 0.f);

	// for each pair in the objects map (in this case, one Windmill called "windmill")
		// pair is type <string, DisplayableObject*> so must call on 'second' element
	for (map <string, DisplayableObject*>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
	{
		itr->second->display();
	}

	checkGLError();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // Initialise GL environment
	setup();                        // Call additional initialisation commands
	glutDisplayFunc(draw);          // Register scene to render contents of draw() function
	glutReshapeFunc(reshape);		// Register scene to render contents of reshape() function
	checkGLError();                 // Check any OpenGL errors in initialisation
	glutMainLoop();                 // Begin rendering sequence
	return 0;
}

void checkGLError()
{
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}