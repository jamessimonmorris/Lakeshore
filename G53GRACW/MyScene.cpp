#include "MyScene.h"

void setup()
{
	width = 1200;                                   // initialise global window variables
	height = 800;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("My Scene");                   // create and show window (named MyScene)

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	cameraRadius();                     // initialise camrad variable (based on window height)
	Stage* stage = new Stage();         // new instance of Stage object    
	stage->size(camrad);                // resize to bound scene
	objects["_stage"] = stage;           // Add to objects map with id "stage"

	Windmill* windmill = new Windmill();
	windmill->size(75.f);
	objects["windmill"] = windmill;

	srand((int)time(0));							// Seed rand() using current time

	Tree* tree = new Tree(randomNumGen());
	tree->position(500.f, 0.f, 0.f);
	tree->size(75.f);
	objects["tree"] = tree;

	Tree* tree1 = new Tree(randomNumGen());
	tree1->position(-360.f, 0.f, -173.f);
	tree1->size(75.f);
	objects["tree1"] = tree1;
	
	reshape(width, height);
	prevTime = glutGet(GLUT_ELAPSED_TIME);

	cen[0] = 0.f;
	cen[1] = 0.f;
	cen[2] = 0.f;
}

float runtime()
{
	int currTime = glutGet(GLUT_ELAPSED_TIME);      // number of milliseconds since start of program
	float dT = static_cast<float>(currTime - prevTime) / 1000.f; // calculate time difference between calls to runtime
	prevTime = currTime;                            // update time variable
	return dT;                                      // return time change
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
	gluPerspective(60.0, aspect, 1.0, camrad*10.f);
	//glOrtho(-width/2.f, width/2.f, -height/2.f, height/2.f, 1.f, camrad*2.f);       // orthographic
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW); // return matrix mode to modelling and viewing
}

void draw()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	positionCamera();

	glEnable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);

	glTranslatef(0.f, -height / 2.f, 0.f);
	glColor3f(0.f, 0.f, 0.f);

	// calculate runtime between now and last draw call
	float dT = runtime();
	Animation* ani_obj;

	// for each pair in the objects map (in this case, one Windmill called "windmill")
		// pair is type <string, DisplayableObject*> so must call on 'second' element
	for (map <string, DisplayableObject*>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
	{
		ani_obj = dynamic_cast<Animation*>(itr->second);
		if (ani_obj != NULL) ani_obj->update(dT);        // update if subclasses Animation
		itr->second->display();                         // call display method on DisplayableObject
	}

	checkGLError();
	glutSwapBuffers();
}

void positionCamera()
{
	cameraRadius();                                 // calculate current camera position
	eye[0] = camrad * sin(camangle);                  // set eye x (at camrad*sin(0)[ = 0])
	eye[1] = 840.f;
	//eye[1] = cen[1];                                // set eye y (at 0)
	eye[2] = camrad * cos(camangle);                  // set eye z (at camrad*cos(0)[ = 1])
	gluLookAt(eye[0], eye[1], eye[2],               // eye position
		cen[0], cen[1], cen[2],               // point that you are looking at (origin)
		0.f, 1.f, 0.f);                       // up vector (0, 1 0)
}

void cameraRadius()
{
	camrad = (height / 2.f) / tan(M_PI / 24.f);
	//camrad = (height / 2.f) / tan(M_PI / 8.f);      // calcualte camera radius based on height
}

void keyPressed(int keyCode, int xm, int ym)
{	// Special (coded) key pressed
	float incr = (float)M_PI / 36.f;   // increment angle by 5 degrees
	if (keyCode == GLUT_KEY_LEFT)
	{                      // left arrow (move camera left around scene)
		camangle -= incr;     // decrement camera angle
	}
	else if (keyCode == GLUT_KEY_RIGHT)
	{              // right arrow (move camera right around scene)
		camangle += incr;     // increment camera angle
	}
}

void keyPressed(unsigned char key, int xm, int ym)
{	// ASCII key pressed
	float incr = (float)M_PI / 36.f;
	if (key == ' ')
	{                                     // if space bar pressed
		camangle = 0.f;                   //reset angle to 0.0
	}
	else if (key == 'a')
	{
		camangle -= incr;
	}
	else if (key == 'd')
	{
		camangle += incr;
	}
}

// TODO: Implement mouse functions

float randomNumGen()
{
	ranNum = (float) ((rand() % 21) + 30);

	printf("%f\n", ranNum);

	return ranNum;
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

void destroyObjects()
{
	for (map <string, DisplayableObject*>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
	{
		delete itr->second;                         // delete all objects from memory
	}
	objects.clear();                                // clear map
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // Initialise GL environment
	setup();                        // Call additional initialisation commands
	glutDisplayFunc(draw);          // Register scene to render contents of draw() function
	glutIdleFunc(draw);				// Register scene to draw content on back buffer
	glutReshapeFunc(reshape);		// Register reshape function to handle window resizing
	glutKeyboardFunc(keyPressed);	// ASCII key handling
	glutSpecialFunc(keyPressed);	// Coded key handling
	checkGLError();                 // Check any OpenGL errors in initialisation
	glutMainLoop();                 // Begin rendering sequence
	destroyObjects();				// Run upon exit
	return 0;
}
