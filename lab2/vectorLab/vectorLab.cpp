#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"
#include "vector.h"
#include "glut.h"             // OpenGL utilties

using namespace MyOGLProg;

#include "stdlib.h"
#include <iostream>

//prototypes for our callback functions
void DisplayScene(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void Answer1(void);
void Answer2(Position);
void Answer3(Position);
void Answer4(Position);
void Answer5(Position);
void Answer6(void);
void Answer7(void);

int answer = 0;


void DrawVector(Position& startPos, Vector& v1)
{
	//draw the vector v1 starting from position startPos
	//this function will only work as long as the z coordinate for both positions is zero
	float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	Vector v;
	if (length > 0.0){ v.x = v1.x/length; v.y = v1.y/length; v.z = v1.z/length; }
	else return;
	float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0);
	float a = RAD2DEG(acos(d));
	if (v.x > 0.0) a = -a;

	glPushMatrix();
	glTranslatef(startPos.x, startPos.y, startPos.z);
	glRotatef(a,0.0,0.0,1.0);
	float space = 0.25;
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, length, 0.0);

	glVertex3f(0.0, length, 0.0);
	glVertex3f(-space, length - (space * 1.5), 0.0);

	glVertex3f(0.0, length, 0.0);
	glVertex3f(space, length - (space * 1.5), 0.0);
	glEnd();
	glPopMatrix();
}

//our main routine
int main(int argc, char *argv[])
{
	
	std::cout << "Press a key between 1-7 to see answer for corresponding question. Press esc to quit." << std::endl;
	//Initialise Glut and create a window
	glutInit(&argc, argv);
	//sets up our display mode
	//here we've selected an RGBA display with depth testing 
	//and double buffering enabled
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//create a window and pass through the windows title
	glutCreateWindow("Basic Glut Application");

	//run our own drawing initialisation routine
	init_drawing();

	//tell glut the names of our callback functions point to our 
	//functions that we defined at the start of this file
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutDisplayFunc(DisplayScene);

	//request a window size of 600 x 600
	glutInitWindowSize(600,600);
	glutReshapeWindow(600,600);

	//go into the main loop
	//this loop won't terminate until the user exits the 
	//application
	glutMainLoop();

	return 0;
}



/*****************************************************************************
DisplayScene()

The work of the application is done here. This is called by glut whenever the 
//window needs to be redrawn
*****************************************************************************/

void DisplayScene(void)
{
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	glTranslatef(-3.0,-3.0,-10.0);

	/*glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(0.0,0.0,-5.0);
	glEnd();*/

	GLfloat yellow[4] = { 1.0f, 1.0f, 0.2f, 1.0f };
	GLfloat blue[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	GLfloat green[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
	Position origin;
	origin.x = origin.y = origin.z = 0.0;

	switch (answer) {
	case 1: Answer1();
		break;
	case 2: Answer2(origin);
		break;
	case 3: Answer3(origin);
		break;
	case 4: Answer4(origin);
		break;
	case 5: Answer5(origin);
		break;
	case 6: Answer6();
		break;
	case 7: Answer7();
		break;
	}

	//draw a red horizontal line, one unit long
	glLineWidth(3.0);
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0,0.0);
	glEnd();
	glPopMatrix();

	//draw a green vertical line, one unit high
	glLineWidth(3.0);
	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(0.0,0.0);
	glVertex2f(0.0,1.0);
	glEnd();
	glPopMatrix();

	//draw a white point at the origin
	glPointSize(2.0);
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0,0.0);
	glEnd();
	glPopMatrix();


	//flush what we've drawn to the buffer
	glFlush();
	//swap the back buffer with the front buffer
	glutSwapBuffers();
}

/*b1. Place the vector (4.0, 2.0, 0.0) at position (1.0,2.0,0.0).*/
void Answer1() {
	std::cout << "b1. Place the vector (4.0, 2.0, 0.0) at position (1.0,2.0,0.0). \n\n\n\n" << std::endl;
	//define a position and a vector
	Position p1;
	p1.x = 1.0; p1.y = 2.0; p1.z = 0.0;
	Vector v1(4.0, 2.0, 0.0);

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0,1.0,0.0);
	DrawVector(p1,v1);
}

/*b2. Given the vector (4.0, 2.0, 0.0) starting at the origin, add the vector (-2.0, 3.0, 0.0) and map the final position.*/
void Answer2(Position origin) {
	std::cout << "b2. Given the vector (4.0, 2.0, 0.0) starting at the origin, add the vector (-2.0, 3.0, 0.0) and map the final position. \n\n\n\n" << std::endl;
	//define 3 vectors
	Vector v1(4.0, 2.0, 0.0);
	Vector v2(-2.0,3.0,0.0);
	Vector v3 = v1.addTo(v2);

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0,1.0,0.0);
	DrawVector(origin,v3);
}

/*b3. Find the angle between the vectors (0.0,1.0,0.0) and (0.707,0.707,0.0). Draw both vectors starting at the origin.*/
void Answer3(Position origin) {
	std::cout << "b3. Find the angle between the vectors (0.0,1.0,0.0) and (0.707,0.707,0.0). Draw both vectors starting at the origin. \n" << std::endl;
	//define a position and a vector
	Vector v1(0.0, 1.0, 0.0);
	Vector v2(0.707,0.707,0.0);

	float cosAngle = v1.getDotProduct(v2)/(v1.getMagnitude()*v2.getMagnitude());
	RAD2DEG(cos(cosAngle));
	std::cout << "cosAngle: " << cosAngle << std::endl;
	std::cout << "cos(cosAngle): " << cos(cosAngle) << std::endl;
	std::cout << "Angle:" << RAD2DEG(cos(cosAngle))  << "\n\n\n" << std::endl;

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0,1.0,0.0);
	DrawVector(origin,v1);
	DrawVector(origin,v2);

}

/*b4. Determine, using the dot product, if the vectors (4.0,4.0,0.0) and (-2.0, 3.0, 0.0) point in the same direction. Draw both vectors starting at the origin.*/
void Answer4(Position origin) {
	std::cout << "b4. Determine, using the dot product, if the vectors (4.0,4.0,0.0) and (-2.0, 3.0, 0.0) point in the same direction. Draw both vectors starting at the origin. \n" << std::endl;
	//define a position and a vector
	Vector v1(4.0,4.0,0.0);
	Vector v2(-2.0, 3.0, 0.0);

	float dotProduct = v1.getDotProduct(v2);
	if(dotProduct > 0)
		std::cout << "The vectors point in the same direction \n\n\n" << std::endl;
	else if(dotProduct < 0)
		std::cout << "The vectors don't point in the same direction \n\n\n" << std::endl;
	else if(dotProduct == 0)
		std::cout << "The vectors are perpendicular \n\n\n" << std::endl;

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0,1.0,0.0);
	DrawVector(origin,v1);
	DrawVector(origin,v2);
}

/*b5. Project the point (5.0,4.0,0.0) onto the line (0.0,0.0,0.0) to (3.0,9.0,0.0).*/
void Answer5(Position origin) {
	std::cout << "b5. Project the point (5.0,4.0,0.0) onto the line (0.0,0.0,0.0) to (3.0,9.0,0.0). \n\n\n\n" << std::endl;
	//define 2 vectors
	Vector v1(3.0,9.0,0.0);
	Vector v2(5.0,4.0,0.0);

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(2.0);
	glColor3f(1.0,0.0,0.0);
	DrawVector(origin,v1);
	glColor3f(0.0,1.0,0.0);
	DrawVector(origin,v2);

	v1.setMagnitude(v2.getMagnitude());
	//draw a yellow point at the projection
	glPointSize(5.0);
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glBegin(GL_POINTS);
	glVertex2f(v1.x,v1.y);
	glEnd();
	glPopMatrix();
}

/*b6. Find the angle between the line from (1.0,8.0,0.0) to (5.0,4.0,0.0) and the line from (3.0,0.0,0.0) to (-6.0,0.0,0.0)*/
void Answer6() {
	std::cout << "b6. Find the angle between the line from (1.0,8.0,0.0) to (5.0,4.0,0.0) and the line from (3.0,0.0,0.0) to (-6.0,0.0,0.0) \n" << std::endl;
	//define two positions and vectors
	Position p1;
	p1.x = 1.0; p1.y = 8.0; p1.z = 0.0;
	Position p2;
	p2.x = 3.0; p2.y = 0.0; p2.z = 0.0;

	Vector v1(5.0-1.0,4.0-8.0,0.0);
	Vector v2(-6.0-3.0,0.0,0.0);

	float cosAngle = v1.getDotProduct(v2)/(v1.getMagnitude()*v2.getMagnitude());
	RAD2DEG(cos(cosAngle));
	std::cout << "cosAngle: " << cosAngle << std::endl;
	std::cout << "cos(cosAngle): " << cos(cosAngle) << std::endl;
	std::cout << "Angle: " << RAD2DEG(cos(cosAngle)) << "\n\n\n" << std::endl;

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0,1.0,0.0);
	DrawVector(p1,v1);
	DrawVector(p2,v2);
}

/*b7. Determine the closest point on the line from (-2.5, -2.0, 0.0) to (5.0, -2.0, 0.0) to the position (8.0,3.0, 0.0).*/
void Answer7() {
	std::cout << "b7. Determine the closest point on the line from p1(-2.5, -2.0, 0.0) to p2(5.0, -2.0, 0.0) to the position (8.0,3.0, 0.0).\n" << std::endl;
	Position p1;
	p1.x = -2.5; p1.y = -2.0; p1.z = 0.0;
	Position p2;
	p2.x = 5.0; p2.y = -2.0; p1.z = 0.0;

	Position p3;
	p3.x = 8.0; p3.y = 3.0; p3.z = 0.0;

	//define 2 vectors
	Vector v1(7.5,0.0,0.0);
	Vector v2(0.0,-100,0.0);

	//Since the perpendicular vector doesn't interesect the point the shortest distance is from either of the end points
	if (abs(p3.x-p1.x + p3.y-p1.y) < abs(p3.x-p2.x + p3.y-p2.y))
		std::cout << "p1 is closest to p3 \n\n\n" << std::endl;
	else
		std::cout << "p2 is closest to p3 \n\n\n" << std::endl;

	

	//draw the vector at position
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(2.0);
	glColor3f(1.0,0.0,0.0);
	DrawVector(p1,v1);
	DrawVector(p3,v2);

	//draw a yellow point at the projection
	glPointSize(5.0);
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();
	glBegin(GL_POINTS);
	glVertex2f(p3.x,p3.y);
	glEnd();
	glPopMatrix();
}


//idle callback function - this is called when there is nothing 
//else to do
void idle(void)
{
	//this is a good place to do animation
	//since there are no animations in this test, we can leave 
	//idle() empty
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27: //27 is the ASCII code for the ESCAPE key
		exit(0);
		break;
	case 49:
		answer = 1;
		DisplayScene();
		break;
	case 50:
		answer = 2;
		DisplayScene();
		break;
	case 51:
		answer = 3;
		DisplayScene();
		break;
	case 52:
		answer = 4;
		DisplayScene();
		break;
	case 53:
		answer = 5;
		DisplayScene();
		break;
	case 54:
		answer = 6;
		DisplayScene();
		break;
	case 55:
		answer = 7;
		DisplayScene();
		break;

	}
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
	//set the viewport to be the same width and height as the window
	glViewport(0,0,width, height);
	//make changes to the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set up our projection type
	//we'll be using a perspective projection, with a 90 degree 
	//field of view
	gluPerspective(45.0, (float) width / (float) height, 1.0, 100.0);
	//redraw the view during resizing
	DisplayScene();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
void init_drawing(void)
{
	//blend colours across the surface of the polygons
	//another mode to try is GL_FLAT which is flat shading
	glShadeModel(GL_SMOOTH);
	//turn lighting off
	glDisable(GL_LIGHTING);
	//enable OpenGL hidden surface removal
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_DEPTH_TEST);

	//glClearColor(1.0,0.0,0.0,0.0);
}