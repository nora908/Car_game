#include <iostream>
#include <random>
#include <cmath>
#include <glew.h>
#include <freeglut.h>
using namespace std;



clock_t collisionTime = 0;
clock_t elapsedTime = 0;
// car cube positions
float PositionX = 0.0;
float PositionY = 0.0;
float PositionZ = -20.0;

//function to  generate rendom numbers

int random(int min , int max) {
	std::random_device rd;  // Obtain a random seed from the hardware
	std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(min, max);  // Define the range

	int random_number = dis(gen);  // Generate a random number within the range

	//std::cout << "Random number: " << random_number << std::endl;

	return random_number;
}


float obstacle1X = random(-30, 30);
float obstacle1Y = 0.0;
float obstacle1Z = random(-100, -30);

float obstacle2X = random(-30, 30);
float obstacle2Y = 0.0;
float obstacle2Z = random(-100, -30);

float obstacle3X = random(-30, 30);
float obstacle3Y = 0.0;
float obstacle3Z = random(-100, -30);

float obstacle4X = random(-30, 30);
float obstacle4Y = 0.0;
float obstacle4Z = random(-100, -30);



static int frameCount = 0; // Number of frames
static int delta = 1.0;  //coordinates change 
static int isCollision = 0; // Is there collision between the spacecraft and an asteroid?
const int restartDelay = 3000; // 3 seconds
/////////////////////

// Routine to draw a bitmap character string.
void writeBitmapString(void* font, const char* string)
{
	const char* c;

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

// Routine to count the number of frames drawn every second.
void frameCounter(int value)
{
	if (value != 0) // No output the first time frameCounter() is called (from main()).
		std::cout << "FPS = " << frameCount << std::endl;
	frameCount = 0;
	glutTimerFunc(1000, frameCounter, 1);
}
void restartGame(int value)
{
	if (value == 0) {
		// Reset the variables to their initial values
		PositionX = 0.0;
		PositionY = 0.0;
		PositionZ = -20.0;
		obstacle1X = random(-30, 30);
		obstacle1Y = 0.0;
		obstacle1Z = random(-100, -30);

		obstacle2X = random(-30, 30);
		obstacle2Y = 0.0;
		obstacle2Z = random(-100, -30);

		obstacle3X = random(-30, 30);
		obstacle3Y = 0.0;
		obstacle3Z = random(-100, -30);

		obstacle4X = random(-30, 30);
		obstacle4Y = 0.0;
		obstacle4Z = random(-100, -30);


		isCollision = false;
		delta = 1.0;

		glutPostRedisplay(); // Request a redraw to see the updated game state
	}
}


void drawScene(void)
{

	frameCount++; // Increment number of frames every redraw.
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(PositionX, PositionY+10, PositionZ+10, PositionX, PositionY+10, PositionZ+5, 0.0, 1.0, 0.0);


	if (isCollision)
	{
		
		
		// Render the "you lose" message
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		//glRasterPos3f(-3.5, 30.0, -65.0);
		glRasterPos3f(-3.5, 10.0, -100.0);

		writeBitmapString(GLUT_BITMAP_HELVETICA_18, "  you lose !  ");
		glPopMatrix();
	}
	if (PositionZ == -105) //the target is reached
	{
		// Render the " you win " message
		glColor3f(0.0, 0.5, 0.0);
		glPushMatrix();
		glRasterPos3f(-3.5, 10.0, PositionZ -30.0);
		
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, " ** you win **  ");
		glPopMatrix();

	}
	//the ground
	glColor3f(0.1, 0.2, 0.4);
	glBegin(GL_QUADS);
	glVertex3f(-40.0, -2.5, -5.0);
	glVertex3f(40.0, -2.5, -5.0);
	glVertex3f(400.0, -2.5, -200.0);
	glVertex3f(-400.0, -2.5, -200.0);
	glEnd();


	

	//the far with Golden Yellow
	glColor3f(0.98, 0.85, 0.37);
	glBegin(GL_QUADS);
	glVertex3f(-400.0, -2.5, -200.0);
	glVertex3f(400.0, -2.5, -200.0);
	glVertex3f(400.0, 400.0, -200.0);
	glVertex3f(-400.0, 400.0, -200.0);
	glEnd();

	


	
	////the target
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-200.0, 0.0, -100.0);
	glVertex3f(200.0, 0.0, -100.0);
	glVertex3f(200.0, 0.0, -110.0);
	glVertex3f(-200.0, 0.0, -110.0);
	glEnd();

	

	//an obstacle cube_1
	glColor3f(0.0, 0.75, 1.0);
	glPushMatrix();
	glTranslatef(obstacle1X, obstacle1Y, obstacle1Z);
	glutSolidCube(3.0);
	glPopMatrix();

	//an obstacle cube_2
	glColor3f(1.0, 0.5, 0.31);
	glPushMatrix();
	glTranslatef(obstacle2X, obstacle2Y, obstacle2Z);
	glutSolidCube(3.0);
	glPopMatrix();

	//an obstacle cube_3
	glColor3f(0.37, 0.69, 0.63);
	glPushMatrix();
	glTranslatef(obstacle3X, obstacle3Y, obstacle3Z);
	glutSolidCube(3.0);
	glPopMatrix();

	//an obstacle cube_4
	
	glColor3f(0.86, 0.12, 0.24);
	glPushMatrix();
	glTranslatef(obstacle4X, obstacle4Y, obstacle4Z);
	glutSolidCube(3.0);
	glPopMatrix();


	//the car cube
	glColor3f(1.0, 0.59, 0.48);
	glPushMatrix();
	glTranslatef(PositionX, PositionY, PositionZ);
	glutSolidCube(5.0);
	glPopMatrix();

	//bottom right tire
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(PositionX + 3, PositionY, PositionZ - 1.5);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();


	//top right tire
	glPushMatrix();
	glTranslatef(PositionX + 3, PositionY, PositionZ + 1.5);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	//bottom left tire
	glPushMatrix();
	glTranslatef(PositionX - 3, PositionY, PositionZ - 1.5);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();


	//top left tire
	glPushMatrix();
	glTranslatef(PositionX - 3, PositionY, PositionZ + 1.5);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

                  


	glutSwapBuffers();
}

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(0, frameCounter, 0); // Initial call of frameCounter().
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}



// for Collision detection
void checkCollision(void)
{
	if ((PositionX - obstacle1X) * (PositionX - obstacle1X) + (PositionZ - obstacle1Z) * (PositionZ - obstacle1Z) <= 4.0 * 4.0
		|| (PositionX - obstacle2X) * (PositionX - obstacle2X) + (PositionZ - obstacle2Z) * (PositionZ - obstacle2Z) <= 4.0 * 4.0
		|| (PositionX - obstacle3X) * (PositionX - obstacle3X) + (PositionZ - obstacle3Z) * (PositionZ - obstacle3Z) <= 4.0 * 4.0
		|| (PositionX - obstacle4X) * (PositionX - obstacle4X) + (PositionZ - obstacle4Z) * (PositionZ - obstacle4Z) <= 4.0 * 4.0)
	{

		isCollision = 1;
		delta = 0;

		// Schedule the restart of the game after the specified delay
		glutTimerFunc(restartDelay, restartGame, 0);
	}
}
void winning_detection(void)
{
	if (PositionZ == -105)
	{
		delta = 0;
		glutTimerFunc(restartDelay, restartGame, 0);
	}
}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;


	}
}

void specialKeyInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		PositionX += delta; // Move to the right
		checkCollision();
		winning_detection();
		break;
	case GLUT_KEY_LEFT:
		PositionX -= delta; // Move to the left
		checkCollision();
		winning_detection();
		break;
	case GLUT_KEY_UP:
		PositionZ -= delta; // Move forward
		checkCollision();
		winning_detection();
		break;
	case GLUT_KEY_DOWN:
		PositionZ += delta; // Move backward
		checkCollision();
		winning_detection();
		break;
	}
	glutPostRedisplay(); // Request a redraw to see the updated cube position
}


// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("box.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glutSpecialFunc(specialKeyInput); // Register the special key callback


	glewExperimental = GL_TRUE;
	glewInit();

	setup();
	glutMainLoop();
	
}





