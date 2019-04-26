#include "MyScene.h"

void setup()
{
	width = 1200;                                   // initialise global window variables
	height = 800;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("Lakeshore");                   // create and show window (named MyScene)

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	
	cameraRadius();                     // initialise camrad variable (based on window height)
	Stage* stage = new Stage();         // new instance of Stage object    
	stage->size(camrad * 5.f, camrad * 2.f, camrad * 5.f);                // resize to bound scene
	GLuint* skybox = new GLuint[6];
	skybox[0] = textureManager.loadImage("Textures/skybox/left.bmp");
	skybox[1] = textureManager.loadImage("Textures/skybox/right.bmp");
	skybox[2] = textureManager.loadImage("Textures/skybox/far.bmp");
	skybox[3] = textureManager.loadImage("Textures/skybox/near.bmp");
	skybox[4] = textureManager.loadImage("Textures/skybox/floor.bmp");
	skybox[5] = textureManager.loadImage("Textures/skybox/up.bmp");
	stage->setTextures(skybox);
	objects["_stage"] = stage;           // Add to objects map with id "stage"

	GLuint brick = textureManager.loadImage("Textures/brick.bmp"); if (brick != NULL) printf("brick loaded\n");
	GLuint roof = textureManager.loadImage("Textures/roof.bmp"); if (roof != NULL) printf("roof loaded\n");
	GLuint rotorWood = textureManager.loadImage("Textures/rotorwood.bmp"); if (rotorWood != NULL) printf("rotor wood loaded\n");
	GLuint rotorFabric = textureManager.loadImage("Textures/rotorfabric.bmp"); if (rotorFabric != NULL) printf("rotor fabric loaded\n");
	GLuint metal = textureManager.loadImage("Textures/metal1.bmp"); if (metal != NULL) printf("metal loaded\n");
	windmill[0] = new Windmill(brick, roof, rotorWood, rotorFabric, metal);
	windmill[0]->position(200.f, 0.f, 2800.f);
	windmill[0]->orientation(0.f, -30.f, 0.f);
	windmill[0]->size(1.3 * scale);
	objects["windmill"] = windmill[0];

	GLuint board = textureManager.loadImage("Textures/sign.bmp"); if (board != NULL) printf("sign loaded\n");
	GLuint backboard = textureManager.loadImage("Textures/backboard.bmp"); if (backboard != NULL) printf("backboard loaded\n");
	sign[0] = new Sign(metal, board, backboard);
	sign[0]->position(-2400.f, 0.f, 3750.f);
	sign[0]->orientation(-2.f, 8.f, 0.f);
	sign[0]->size(scale);
	objects["sign"] = sign[0];

	srand((int)time(0));							// Seed rand() using current time

	GLuint house1 = textureManager.loadImage("Textures/house1.bmp"); if (house1 != NULL) printf("house1 loaded\n");
	GLuint house2 = textureManager.loadImage("Textures/house2.bmp"); if (house2 != NULL) printf("house2 loaded\n");
	GLuint church = textureManager.loadImage("Textures/church.bmp"); if (church != NULL) printf("church loaded\n");
	GLuint door1 = textureManager.loadImage("Textures/door1.bmp"); if (door1 != NULL) printf("door1 loaded\n");
	GLuint door2 = textureManager.loadImage("Textures/door2.bmp"); if (door2 != NULL) printf("door2 loaded\n");
	GLuint door3 = textureManager.loadImage("Textures/door3.bmp"); if (door3 != NULL) printf("door3 loaded\n");
	GLuint garage1 = textureManager.loadImage("Textures/garage1.bmp"); if (garage1 != NULL) printf("garage1 loaded\n");
	GLuint garage2 = textureManager.loadImage("Textures/garage2.bmp"); if (garage2 != NULL) printf("garage2 loaded\n");
	house[0] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[0]->orientation(0.f, 90.f, 0.f);
	house[0]->position(-3500.f, 0.f, 600.f);
	house[0]->size(scale);
	objects["house"] = house[0];

	house[1] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[1]->position(-900.f, 0.f, -3500.f);
	house[1]->size(scale);
	objects["house1"] = house[1];

	house[2] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[2]->orientation(0.f, 90.f, 0.f);
	house[2]->position(-3500.f, 0.f, -1850.f);
	house[2]->size(scale);
	objects["house2"] = house[2];

	house[3] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[3]->orientation(0.f, -105.f, 0.f);
	house[3]->position(3100.f, 0.f, 2184.f);
	house[3]->size(scale);
	objects["house3"] = house[3];

	house[4] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[4]->orientation(0.f, 90.f, 0.f);
	house[4]->position(-2950.f, 0.f, 3200.f);
	house[4]->size(scale);
	objects["house4"] = house[4];

	house[5] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[5]->orientation(0.f, -45.f, 0.f);
	house[5]->position(2600.f, 0.f, -3750.f);
	house[5]->size(scale);
	objects["house5"] = house[5];

	house[6] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[6]->orientation(0.f, -90.f, 0.f);
	house[6]->position(2700.f, 0.f, -950.f);
	house[6]->size(0.8 * scale);
	objects["house6"] = house[6];

	house[7] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[7]->orientation(0.f, 90.f, 0.f);
	house[7]->position(2900.f, 0.f, 74.f);
	house[7]->size(0.8 * scale);
	objects["house7"] = house[7];

	house[8] = new House(randomNumGen(), roof, brick, church, house1, house2, door1, door2, door3, garage1, garage2);
	house[8]->position(2000.f, 0.f, 180.f);
	house[8]->size(0.8 * scale);
	objects["house8"] = house[8];

	GLuint bark = textureManager.loadImage("Textures/bark.bmp");
	GLuint leaves = textureManager.loadImage("Textures/leaves1.bmp");

	// Block 2 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(556.f, 0.f, 2344.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-350.f, 0.f, 2455.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(650.f, 0.f, 3200.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-650.f, 0.f, 3050.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-584.f, 0.f, 2703.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, 2700.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-100.f, 0.f, 2350.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(210.f, 0.f, 2200.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(500.f, 0.f, 2050.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-500.f, 0.f, 2250.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-200.f, 0.f, 2075.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(100.f, 0.f, 1920.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 4 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-1965.f, 0.f, 735.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-1982.f, 0.f, -835.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-2258.f, 0.f, -705.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 3 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3250.f, 0.f, 1875.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3450.f, 0.f, 2325.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3400.f, 0.f, 2000.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3450.f, 0.f, 3100.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3500.f, 0.f, 3350.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3400.f, 0.f, 3600.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3150.f, 0.f, 3475.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(2035.f, 0.f, 3675.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(1900.f, 0.f, 3425.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 9 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3300.f, 0.f, -3475.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3540.f, 0.f, -3625.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3650.f, 0.f, -3350.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3450.f, 0.f, -2000.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3660.f, 0.f, -2200.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3330.f, 0.f, -2275.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 1 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3600.f, 0.f, 3625.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3250.f, 0.f, 3575.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3700.f, 0.f, 3325.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3300.f, 0.f, 3125.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3525.f, 0.f, 2990.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3605.f, 0.f, 2750.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3510.f, 0.f, 2525.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3600.f, 0.f, 2255.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3355.f, 0.f, 2100.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-3200.f, 0.f, 2750.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-2950.f, 0.f, 3700.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-2650.f, 0.f, 3580.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 7 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-2015.f, 0.f, -3435.f);
	tree[treeItr]->size(1.5 * scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 6 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3280.f, 0.f, 450.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3596.f, 0.f, 600.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(3364.f, 0.f, 860.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 8 trees
	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, -3600.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, -3300.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, -3000.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, -2700.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, -2400.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f, 0.f, -2100.f);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	// Block 5 trees
	int range = 75;
	float variation = (rand() % range) - (range / 2) - 1;
	float variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f + variation, 0.f, 700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f + variation, 0.f, 420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f + variation, 0.f, 140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f + variation, 0.f, -140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f + variation, 0.f, -420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(700.f + variation, 0.f, -700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];



	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(420.f + variation, 0.f, 700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(420.f + variation, 0.f, 420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(420.f + variation, 0.f, 140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(420.f + variation, 0.f, -140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(420.f + variation, 0.f, -420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(420.f + variation, 0.f, -700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];



	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(140.f + variation, 0.f, 700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(140.f + variation, 0.f, 420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(140.f + variation, 0.f, 140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(140.f + variation, 0.f, -140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(140.f + variation, 0.f, -420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(140.f + variation, 0.f, -700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];



	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-140.f + variation, 0.f, 700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-140.f + variation, 0.f, 420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-140.f + variation, 0.f, 140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-140.f + variation, 0.f, -140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-140.f + variation, 0.f, -420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-140.f + variation, 0.f, -700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];



	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-420.f + variation, 0.f, 700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-420.f + variation, 0.f, 420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-420.f + variation, 0.f, 140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-420.f + variation, 0.f, -140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-420.f + variation, 0.f, -420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-420.f + variation, 0.f, -700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];



	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-700.f + variation, 0.f, 700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-700.f + variation, 0.f, 420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-700.f + variation, 0.f, 140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-700.f + variation, 0.f, -140.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-700.f + variation, 0.f, -420.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

	variation = (rand() % range) - (range / 2) - 1;
	variation1 = (rand() % range) - (range / 2) - 1;

	tree[treeItr] = new Tree(randomNumGen(), bark, leaves);
	tree[treeItr]->position(-700.f + variation, 0.f, -700.f + variation1);
	tree[treeItr]->size(scale);
	objects["tree" + to_string(treeItr)] = tree[treeItr++];

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
		gluPerspective(60.0, aspect, 100.0, camrad * 100.f);
	else
		glOrtho(-width, width, -height, height, 100.f, camrad * 100.f);       // orthographic

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
		//if (itr->first != "_stage") itr->second->size(scale);
		itr->second->display();                         // call display method on DisplayableObject
	}

	checkGLError();
	glutSwapBuffers();
}

void setGlobalLight()
{
	// Set lighting effect colours and positional parameter
	float ambient[] = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
	float diffuse[] = { .8f, .8f, .88f, 1.f };      // diffuse light (50% white)
	//float specular[] = { .953f, .51f, .208f, 1.f };      // specular light (100% white)
	float specular[] = { 1.f, 1.f, 1.f, 1.f };      // specular light (100% white)
	float position[] = { 1.f, .844f, 0.563f, 0.f };      // directional light (w = 0)
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
	switch (keyCode)
	{
	case GLUT_KEY_LEFT:// left arrow (move camera left around scene)
		camangle -= incr;     // decrement camera angle
		break;
	case GLUT_KEY_RIGHT:// right arrow (move camera right around scene)
		camangle += incr;     // increment camera angle
		break;
	case GLUT_KEY_UP:
		if (!ortho)
		{
			camh += 5.f;

			if (camh > 120.f)
				camh = 120.f;
		}
		break;
	case GLUT_KEY_DOWN:
		if (!ortho)
		{
			camh -= 5.f;

			if (camh < 0.f)
				camh = 0.f;
		}
		break;
	case GLUT_KEY_PAGE_UP:
		if (!ortho)
		{
			zoom -= 1.f;

			if (zoom < 7.f)
				zoom = 7.f;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (!ortho)
		{
			zoom += 1.f;

			if (zoom > 30.f)
				zoom = 30.f;
		}
		break;
	}
	printf("Angle: %f; Height: %f; Zoom: %f\n", camangle, camh, zoom);
}

void keyPressed(unsigned char key, int xm, int ym)
{	// ASCII key pressed
	float incr = (float)M_PI / 36.f;

	switch (key)
	{
	case ' ':                                     // if space bar pressed
		camangle = -0.785398f;                   //reset angle to 0.0
		zoom = 24.f;
		camh = 75.f;

		cen[0] = 0.f;
		cen[1] = 0.f;
		cen[2] = 0.f;
		break;
	case 'a':
		camangle -= incr;
		break;
	case 'd':
		camangle += incr;
		break;
	case 'w':
		if (!ortho)
		{
			camh += 5.f;

			if (camh > 120.f)
				camh = 120.f;
		}
		break;
	case 's':
		if (!ortho)
		{
			camh -= 5.f;

			if (camh < 0.f)
				camh = 0.f;
		}
		break;
	case 'e':
		if (!ortho)
		{
			zoom -= 1.f;

			if (zoom < 7.f)
				zoom = 7.f;
		}
		break;
	case 'q':
		if (!ortho)
		{
			zoom += 1.f;

			if (zoom > 30.f)
				zoom = 30.f;
		}
		break;
	case 'g':
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
			camh = 75.f;
		}
		reshape(width, height);
		break;
	case '=':
	case '+':
		for (int i = 0; i < windmills; i++)
		{
			windmill[i]->setRotors((windmill[i]->getRotors()) + 1);
		}
		break;
	case '-':
	case '_':
		for (int i = 0; i < windmills; i++)
		{
			windmill[i]->setRotors((windmill[i]->getRotors()) - 1);
		}
		break;
	case '1':
		view = 1;
		break;
	case '2':
		view = 2;
		break;
	case '3':
		view = 3;
		break;
	case '4':
		view = 4;
		break;
	case '5':
		view = 5;
		break;
	case '6':
		view = 6;
		break;
	case '7':
		view = 7;
		break;
	case '8':
		view = 8;
		break;
	case '9':
		view = 9;
		break;
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
