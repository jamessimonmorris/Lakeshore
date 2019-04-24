#include "MyScene.h"

void setup()
{
	width = 1200;                                   // initialise global window variables
	height = 800;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("The Farm");                   // create and show window (named MyScene)

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	cameraRadius();                     // initialise camrad variable (based on window height)
	Stage* stage = new Stage();         // new instance of Stage object    
	stage->size(camrad * 5.f, camrad * 2.f, camrad * 5.f);                // resize to bound scene
	GLuint* skybox = new GLuint[6];
	skybox[0] = textureManager.loadImage("Textures/skybox/skybox_left.bmp");
	skybox[1] = textureManager.loadImage("Textures/skybox/skybox_right.bmp");
	skybox[2] = textureManager.loadImage("Textures/skybox/skybox_front.bmp");
	skybox[3] = textureManager.loadImage("Textures/skybox/skybox_back.bmp");
	skybox[4] = textureManager.loadImage("Textures/skybox1/floor.bmp");
	skybox[5] = textureManager.loadImage("Textures/skybox/skybox_up.bmp");
	stage->setTextures(skybox);
	objects["_stage"] = stage;           // Add to objects map with id "stage"

	GLuint brick = textureManager.loadImage("Textures/brick.bmp"); if (brick != NULL) printf("brick loaded\n");
	GLuint roof = textureManager.loadImage("Textures/roof.bmp"); if (roof != NULL) printf("roof loaded\n");
	GLuint rotorWood = textureManager.loadImage("Textures/rotorwood.bmp"); if (rotorWood != NULL) printf("rotor wood loaded\n");
	GLuint rotorFabric = textureManager.loadImage("Textures/rotorfabric.bmp"); if (rotorFabric != NULL) printf("rotor fabric loaded\n");
	windmill[0] = new Windmill(brick, roof, rotorWood, rotorFabric);
	windmill[0]->orientation(0.f, -13.3f, 0.f);
	windmill[0]->size(scale);
	objects["windmill"] = windmill[0];

	srand((int)time(0));							// Seed rand() using current time

	GLuint bark = textureManager.loadImage("Textures/bark.bmp");
	GLuint leaves = textureManager.loadImage("Textures/leaves1.bmp");
	tree[0] = new Tree(randomNumGen(), bark, leaves);
	tree[0]->position(556.f, 0.f, -456.f);
	tree[0]->size(scale);
	objects["tree"] = tree[0];

	tree[1] = new Tree(randomNumGen(), bark, leaves);
	tree[1]->position(-350.f, 0.f, -345.f);
	tree[1]->size(scale);
	objects["tree1"] = tree[1];

	tree[2] = new Tree(randomNumGen(), bark, leaves);
	tree[2]->position(650.f, 0.f, 550.f);
	tree[2]->size(scale);
	objects["tree2"] = tree[2];

	tree[3] = new Tree(randomNumGen(), bark, leaves);
	tree[3]->position(-650.f, 0.f, 250.f);
	tree[3]->size(scale);
	objects["tree3"] = tree[3];

	tree[4] = new Tree(randomNumGen(), bark, leaves);
	tree[4]->position(-584.f, 0.f, -97.f);
	tree[4]->size(scale);
	objects["tree4"] = tree[4];

	tree[5] = new Tree(randomNumGen(), bark, leaves);
	tree[5]->position(700.f, 0.f, -100.f);
	tree[5]->size(scale);
	objects["tree5"] = tree[5];
	
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

	if (!ortho)
		gluPerspective(60.0, aspect, 10.0, camrad*100.f);
	else
		glOrtho(-width, width, -height, height, 500.f, camrad*100.f);       // orthographic

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

	float diff = 2800.f;
	switch (view)
	{
	case 1:
		glTranslatef(diff, -height / 3.f, -diff);
		break;
	case 2:
		glTranslatef(0.f, -height / 3.f, -diff);
		break;
	case 3:
		glTranslatef(-diff, -height / 3.f, -diff);
		break;
	case 4:
		glTranslatef(diff, -height / 3.f, 0.f);
		break;
	case 5:
		glTranslatef(0.f, -height / 3.f, 0.f);
		break;
	case 6:
		glTranslatef(-diff, -height / 3.f, 0.f);
		break;
	case 7:
		glTranslatef(diff, -height / 3.f, diff);
		break;
	case 8:
		glTranslatef(0.f, -height / 3.f, diff);
		break;
	case 9:
		glTranslatef(-diff, -height / 3.f, diff);
		break;
	default:
		glTranslatef(0.f, -height / 3.f, 0.f);
		break;
	}
	glColor3f(0.f, 0.f, 0.f);

	glEnable(GL_NORMALIZE);
	setGlobalLight();

	// calculate runtime between now and last draw call
	float dT = runtime();
	Animation* ani_obj;

	// for each pair in the objects map (in this case, one Windmill called "windmill")
		// pair is type <string, DisplayableObject*> so must call on 'second' element
	for (map <string, DisplayableObject*>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
	{
		ani_obj = dynamic_cast<Animation*>(itr->second);
		if (ani_obj != NULL) ani_obj->update(dT);        // update if subclasses Animation
		if (itr->first != "_stage") itr->second->size(scale);
		itr->second->display();                         // call display method on DisplayableObject
	}

	checkGLError();
	glutSwapBuffers();
}

void setGlobalLight()
{
	// Set lighting effect colours and positional parameter
	float ambient[] = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
	float diffuse[] = { .6f, .6f, .6f, 1.f };      // diffuse light (50% white)
	//float specular[] = { .953f, .51f, .208f, 1.f };      // specular light (100% white)
	float specular[] = { 1.f, 1.f, 1.f, 1.f };      // specular light (100% white)
	float position[] = { 1.f, .5f, 1.f, 0.f };      // directional light (w = 0)
	// Attach properties to single light source (GL_LIGHT0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
	glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	// Enable this lighting effects
	glEnable(GL_LIGHTING);  // enable scene lighting (required to enable a light source)
	glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0)    
}

void positionCamera()
{
	cameraRadius();                                 // calculate current camera position
	eye[0] = camrad * sin(camangle);                  // set eye x (at camrad*sin(0)[ = 0])
	eye[1] = camh * zoom;							// set eye y (at 0)
	eye[2] = camrad * cos(camangle);                  // set eye z (at camrad*cos(0)[ = 1])
	gluLookAt(eye[0], eye[1], eye[2],               // eye position
		cen[0], cen[1], cen[2],               // point that you are looking at (origin)
		0.f, 1.f, 0.f);                       // up vector (0, 1 0)
}

void cameraRadius()
{
	camrad = (height / 2.f) / tan(M_PI / zoom);		// calculate camera radius based on height
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
	else if (keyCode == GLUT_KEY_UP && !ortho)
	{
		zoom -= 1.f;

		if (zoom < 10.f)
			zoom = 10.f;
	}
	else if (keyCode == GLUT_KEY_DOWN && !ortho)
	{
		zoom += 1.f;

		if (zoom > 30.f)
			zoom = 30.f;
	}
	else if (keyCode == GLUT_KEY_PAGE_UP && !ortho)
	{
		camh += 5.f;

		if (camh > 120.f)
			camh = 120.f;
	}
	else if (keyCode == GLUT_KEY_PAGE_DOWN && !ortho)
	{
		camh -= 5.f; 

		if (camh < 0.f)
			camh = 0.f;
	}

	printf("Angle: %f; Height: %f; Zoom: %f\n", camangle, camh, zoom);
}

void keyPressed(unsigned char key, int xm, int ym)
{	// ASCII key pressed
	float incr = (float)M_PI / 36.f;
	if (key == ' ')
	{                                     // if space bar pressed
		camangle = -0.785398f;                   //reset angle to 0.0
		zoom = 24.f;
		camh = 45.f;

		cen[0] = 0.f;
		cen[1] = 0.f;
		cen[2] = 0.f;
	}
	else if (key == 'a')
	{
		camangle -= incr;
	}
	else if (key == 'd')
	{
		camangle += incr;
	}
	else if (key == 'w' && !ortho)
	{
		zoom -= 1.f;

		if (zoom < 10.f)
			zoom = 10.f;
	}
	else if (key == 's' && !ortho)
	{
		zoom += 1.f;

		if (zoom > 30.f)
			zoom = 30.f;
	}
	else if (key == 'e' && !ortho)
	{
		camh += 5.f;

		if (camh > 120.f)
			camh = 120.f;
	}
	else if (key == 'q' && !ortho)
	{
		camh -= 5.f;

		if (camh < 0.f)
			camh = 0.f;
	}
	else if (key == 'g')
	{
		if (ortho)
		{
			ortho = false;
			scale = 75.f;
			camh = 45.f;
		}
		else
		{
			ortho = true;
			scale = 50.f;
			camh = 45.f;
		}
		reshape(width, height);
	}
	else if (key == '+' || key == '=')
	{
		for (int i = 0; i < windmills; i++)
		{
			windmill[i]->setRotors((windmill[i]->getRotors()) + 1);
		}
	}
	else if (key == '_' || key == '-')
	{
		for (int i = 0; i < windmills; i++)
		{
			windmill[i]->setRotors((windmill[i]->getRotors()) - 1);
		}
	}
	else if (key == '1')
	{
		view = 1;
	}
	else if (key == '2')
	{
		view = 2;
	}
	else if (key == '3')
	{
		view = 3;
	}
	else if (key == '4')
	{
		view = 4;
	}
	else if (key == '5')
	{
		view = 5;
	}
	else if (key == '6')
	{
		view = 6;
	}
	else if (key == '7')
	{
		view = 7;
	}
	else if (key == '8')
	{
		view = 8;
	}
	else if (key == '9')
	{
		view = 9;
	}

	printf("Angle: %f; Height: %f; Zoom: %f\n", camangle, camh, zoom);
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
