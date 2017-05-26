#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "myvector.h"
#include "mymatrix.h"
using namespace MyMathLibrary;

#include "stdlib.h"
#include "stdio.h"

#include "objloader.h"

ObjMesh* tankBody;
ObjMesh* tankTurret;
ObjMesh* tankMainGun;
ObjMesh* tankSecondaryGun;
ObjMesh* tankWheel;

void load_tank_objs(void);

float zPos = -20.0;
float yRot = 90.0;
float xPos = 0.0;
float yPos = 0.0;

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation

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

  load_tank_objs();


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

void load_tank_objs(void)
{
  tankBody = LoadOBJ(".\\tankobjs\\tankbody.obj");
  tankTurret = LoadOBJ(".\\tankobjs\\tankturret.obj");
  tankMainGun = LoadOBJ(".\\tankobjs\\tankmaingun.obj");
  tankSecondaryGun = LoadOBJ(".\\tankobjs\\tanksecondarygun.obj");
  tankWheel = LoadOBJ(".\\tankobjs\\tankwheel.obj");
  SetTextures(tankBody->m_iMeshID, NULL, ".\\tankobjs\\texture.tga");
}

void draw_tank(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);

	glScalef(0.1,0.1,0.1);		//reduce the size of the tank on screen
	DrawOBJ(tankBody->m_iMeshID);
	
	//Use your own draw code here to draw the rest of the tank
	//Here's the code for each individual part
	//Each part is placed with respect to the origin
	//you'll need to add in glPushMatrix/glTranslatef/glRotatef/glPopMatrix commands as necessary
	
	//draw tankTurret
	glPushMatrix();
	glTranslatef(0.0, 10.5, 0.0);
	DrawOBJ(tankTurret->m_iMeshID);
	glPopMatrix();

	//draw tankMainGun
	glPushMatrix();
	glTranslatef(53.7, -91.8, 11.0);
	DrawOBJ(tankMainGun->m_iMeshID);
	glPopMatrix();
	
	//draw tankSecondaryGun
	glPushMatrix();
	glTranslatef(-12.0, 27.0, -4.0);
	DrawOBJ(tankSecondaryGun->m_iMeshID);
	glPopMatrix();

	//draw wheels
	glPushMatrix();
	glTranslatef(-23.5, -11.0, -57.0);
	for (int i = 0; i < 14; i++) {
		if (i == 7) {
			glTranslatef(47.0, 0.0, -16.0);
			glRotatef(180.0, 0.0, 1.0, 0.0);
		}
		DrawOBJ(tankWheel->m_iMeshID);
		glTranslatef(0.0, 0.0, 16.0);
	}
	glPopMatrix();

	glPopMatrix();
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

  glTranslatef(xPos,yPos,zPos);

  glRotatef(yRot,0.0,1.0,0.0);

  //draw the tank on screen at a position
  draw_tank(0.0, 0.0, 0.0);

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
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
    case 'q':
	  zPos--;
	  break;
	case 'e':
	  zPos++;
	  break;
	case 'r':
		yRot++;
		break;
	case 'f':
		yRot--;
		break;
	case 'a':
		xPos++;
		break;
	case 'd':
		xPos--;
		break;
	case 's':
		yPos++;
		break;
	case 'w':
		yPos--;
		break;
    case 27: //27 is the ASCII code for the ESCAPE key
      exit(0);
      break;
  }
  glutPostRedisplay();
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

  GLfloat specular[] = {0.2,0.2,0.2,1.0};
  GLfloat ambient[] = {1.0,1.0,1.0,1.0};
  GLfloat diffuse[] = {1.0,1.0,1.0,1.0};
  GLfloat position[] = {0.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);

  GLfloat position1[] = {10.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);



  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
}