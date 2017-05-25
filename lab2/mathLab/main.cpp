#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "myquat.h"
#include <iostream>

using namespace MyMathLab;

#include "stdlib.h"

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void draw_square(void);
void draw_quaternion_vector(MyPosition, MyVector, int);

//Global Variables
bool rotateAlongVertice = false;
float degrees = 0;
int task;
GLfloat rotationMatrix[16] = {
	cos(DEG2RAD(degrees)),-sin(DEG2RAD(degrees)),0.0,0.0,
	sin(DEG2RAD(degrees)),cos(DEG2RAD(degrees)),0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0
};

void DrawVector(MyPosition& startPos, MyVector& v1)
{
	//draw the vector v1 starting from position startPos
	//this function will only work as long as the z coordinate for both positions is zero
	float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	MyVector v;
	if (length > 0.0) { v.x = v1.x / length; v.y = v1.y / length; v.z = v1.z / length; }
	else return;
	float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0);
	float a = RAD2DEG(acos(d));
	if (v.x > 0.0) a = -a;

	glPushMatrix();
	glTranslatef(startPos.x, startPos.y, startPos.z);
	glRotatef(a, 0.0, 0.0, 1.0);
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
  glutDisplayFunc(draw);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}

//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
void draw(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  MyPosition myPosition;
  MyVector axisVector;
  MyMatrix myMatrix = MyMatrix();


  switch (task) {

  case 1:
	  //***DO ALL YOUR DRAWING HERE

	  glTranslatef(0.0, 0.0, -10.0);
	  myMatrix.getGLModelviewMatrix();

	  myMatrix.setGLMatrix();

	  //Draw first square
	  glPushMatrix();
	  glTranslatef(1.0, 1.0, -5.0);
	  if (rotateAlongVertice) {
		  glRotatef(degrees, 1.0, 0.0, 0.0);
		  glTranslatef(0.0, 1.0, 0.0);
	  }
	  else {
		  glMultMatrixf(rotationMatrix); //Solution 5
		  //glRotatef(degrees, 0.0, 0.0, 1.0);
	  }
	  draw_square();
	  glPopMatrix();


	  //Draw second square
	  glPushMatrix();
	  glTranslatef(-1.0, 1.0, -5.0);
	  if (rotateAlongVertice) {
		  glRotatef(degrees, -1.0, 0.0, 0.0);
		  glTranslatef(0.0, 1.0, 0.0);
		  rotateAlongVertice = false;
	  }
	  else
		  glRotatef(degrees, 0.0, 0.0, 1.0); //Solution 2
	  draw_square();
	  glPopMatrix();
	  break;

  case 2:
	  glTranslatef(0.0, 0.0, -10.0);

	  myPosition.x = 1.0;
	  myPosition.y = 1.0;
	  myPosition.z = 0.0;
	  axisVector.x = axisVector.y = 0.0; 
	  axisVector.z = 1.0;
	  draw_quaternion_vector(myPosition, axisVector, 45);
	  break;
  case 3:
	  glTranslatef(0.0, 0.0, -50.0);

	  MyPosition myPosition;
	  myPosition.x = 0.0;
	  myPosition.y = -10.0;
	  myPosition.z = 0.0;
	  axisVector.x = 10.0;
	  axisVector.y = axisVector.z = 0.0;
	  axisVector.normalise();
	  std::cout << "axisVectorNorm: " << axisVector.y << std::endl;
	  draw_quaternion_vector(myPosition, axisVector, 45);
	  break;
  }

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

void draw_square(void) {
	//a simple function to draw a square with the current markers orientation and position on screen
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, -1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glEnd();
}

void draw_quaternion_vector(MyPosition myPosition, MyVector axisVector, int degrees) {
	
	axisVector.uniformScale(sin(DEG2RAD(degrees/2)));

	MyPosition origin;
	origin.x = 0.0;
	origin.y = 0.0;
	origin.z = 0.0;
	
	MyQuat qvec = MyQuat(myPosition);
	MyQuat q1 = MyQuat(cos(DEG2RAD(degrees/2)), axisVector);
	MyQuat q1Conj = q1.getConjugate();
	MyQuat qrA = qvec.multiplyBy(q1Conj);
	MyQuat qr = q1.multiplyBy(qrA);

	std::cout << "qvec.w: " << qvec.w << " qvec.v.x: " << qvec.v.x << " qvec.v.y: " << qvec.v.y << " qvec.v.z: " << qvec.v.z << std::endl;
	std::cout << "q1.w: " << q1.w << " q1.v.x: " << q1.v.x << " q1.v.y: " << q1.v.y << " q1.v.z: " << q1.v.z << std::endl;
	std::cout << "q1Conj.w: " << q1Conj.w << " q1Conj.v.x: " << q1Conj.v.x << " q1Conj.v.y: " << q1Conj.v.y << " q1Conj.v.z: " << q1Conj.v.z << std::endl;

	std::cout << "qrA.w: " << qrA.w << " qrA.v.x: " << qrA.v.x << " qrA.v.y: " << qrA.v.y << " qrA.v.z: " << qrA.v.z << std::endl;
	std::cout << "qr.w: " << qr.w << " qr.v.x: " << qr.v.x << " qr.v.y: " << qr.v.y << " qr.v.z: " << qr.v.z << std::endl;

	//draw a red horizontal line, one unit long
	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
	glPopMatrix();

	//draw a green vertical line, one unit high
	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	glPopMatrix();

	//draw a white point at the origin
	glPointSize(2.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0, 0.0);
	glEnd();
	glPopMatrix();

	//draw a yellow point at the start point of the rotation
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_POINTS);
	glVertex2f(myPosition.x, myPosition.y);
	glEnd();
	glPopMatrix();

	//draw a green point at the end point of the rotation
	glPointSize(5.0);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_POINTS);
	glVertex2f(qr.v.x, qr.v.y);
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
	//degrees+=0.05;
	//draw();
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y) {
	std::cout << "k: " << k << std::endl;
  switch(k) {
    case 27: //27 is the ASCII code for the ESCAPE key
      exit(0);
      break;
	case 'v':
		rotateAlongVertice = true;
	case 'r': //114 is the ASCII code for r
		degrees += 5;
		rotationMatrix[0] = cos(DEG2RAD(degrees));
		rotationMatrix[1] = -sin(DEG2RAD(degrees));
		rotationMatrix[4] = sin(DEG2RAD(degrees));
		rotationMatrix[5] = cos(DEG2RAD(degrees));
		break;
	case '1':
		task = 1;
		break;
	case '2':
		task = 2;
		break;
	case '3':
		task = 3;
		break;
  }
  draw();
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
  draw();
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
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
}