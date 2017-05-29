#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "myBoundingSphere.h"
using namespace MyMathLibrary;

#include "stdlib.h"
#include "stdio.h"
#include <iostream>


ObjMesh* tankBody;
ObjMesh* tankTurret;
ObjMesh* tankMainGun;
ObjMesh* tankSecondaryGun;
ObjMesh* tankWheel;
MyBoundingSphere boundingSphereTankBody;
MyBoundingSphere boundingSphereTankTurret;
MyBoundingSphere boundingSphereTankMainGun;
MyBoundingSphere boundingSphereTankSecondaryGun;
MyBoundingSphere boundingSphereTankWheel;
float xProj = 0.0;
float yProj = 0.0;
float zProj = 0.0;

float zPos = -30.0;
float yRot = 0.0;
float xPos = 0.0;
float yPos = 0.0;
float turretRot = 0.0;
float mainGunRot = 0.0;
float secondaryGunRot = 0.0;
float wheelRot = 0.0;
int tankBodyID;
int tankTurretID;
int tankMainGunID;
int tankSecondaryGunID;
int tankWheelID;

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void load_tank_objs(void);
void drawObj(ObjMesh*);
void testIntersect(float, float, float);

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
  
  //Load tankBody into display list
  tankBodyID = glGenLists(1);
  glNewList(tankBodyID, GL_COMPILE);
	drawObj(tankBody);
  glEndList();

  boundingSphereTankBody = MyBoundingSphere(tankBody);

  //Load tankTurret into display list
  tankTurretID = glGenLists(1);
  glNewList(tankTurretID, GL_COMPILE);
	drawObj(tankTurret);
  glEndList();

  boundingSphereTankTurret = MyBoundingSphere(tankTurret);


  //Load tankMainGun into display list
  tankMainGunID = glGenLists(1);
  glNewList(tankMainGunID, GL_COMPILE);
	drawObj(tankMainGun);
  glEndList();

  boundingSphereTankMainGun = MyBoundingSphere(tankMainGun);

  //Load tankSecondaryGun into display list
  tankSecondaryGunID = glGenLists(1);
  glNewList(tankSecondaryGunID, GL_COMPILE);
	drawObj(tankSecondaryGun);
  glEndList();

  boundingSphereTankSecondaryGun = MyBoundingSphere(tankSecondaryGun);


  //Load tankWheel into display list
  tankWheelID = glGenLists(1);
  glNewList(tankWheelID, GL_COMPILE);
	drawObj(tankWheel);
  glEndList();

  //boundingSphereWheel = MyBoundingSphere(tankWheel);
}

void draw_tank(float x, float y, float z) {
	GLUquadricObj *p = gluNewQuadric();

	glPushMatrix();
		glTranslatef(x,y,z);
		glScalef(0.1,0.1,0.1);		//reduce the size of the tank on screen
		glCallList(tankBodyID);

		//Draw projectile
		glPointSize(1.0);
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0.0, 0.0, zProj);
		glBegin(GL_POINTS);
		glVertex2f(xProj, yProj);
		glEnd();
		glPopMatrix();

		//Use your own draw code here to draw the rest of the tank
		//Here's the code for each individual part
		//Each part is placed with respect to the origin
		//you'll need to add in glPushMatrix/glTranslatef/glRotatef/glPopMatrix commands as necessary
	

		//draw tankTurret, rotate it with key 1&2
		glPushMatrix();
			glRotatef(turretRot, 0.0, 1.0, 0.0);
			glTranslatef(0.0, 14.0, 0.0);
			glCallList(tankTurretID);

			//draw tankMainGun, move it up and down with key 3&4
			glPushMatrix();
				glRotatef(mainGunRot, 1.0, 0.0, 0.0);
				glTranslatef(53.7, -102.3, 11.0);
				glCallList(tankMainGunID);

				//Draw boundingSphereTankMainGun
				glPushMatrix();
					glTranslatef(-53.7, 102.3, 55.0);
					glEnable(GL_BLEND);
					glBlendFunc(GL_ONE, GL_ONE);
					gluSphere(p, boundingSphereTankMainGun.radians, 30, 30);
					glDisable(GL_BLEND);
				glPopMatrix();
			glPopMatrix();

			//draw tankSecondaryGun, rotate it with key 5&6
			glPushMatrix();
				glTranslatef(-12.0, 16.5, -15.0);
				glRotatef(secondaryGunRot, 0.0, 1.0, 0.0);
				glTranslatef(0.0, 0.0, 11.0);
				glCallList(tankSecondaryGunID);

				//Draw boundingSphereTankSecondaryGun
				glPushMatrix();
					glTranslatef(0.0, 0.0, 11.0);
					glEnable(GL_BLEND);
					glBlendFunc(GL_ONE, GL_ONE);
					gluSphere(p, boundingSphereTankSecondaryGun.radians, 30, 30);
					glDisable(GL_BLEND);
				glPopMatrix();
			glPopMatrix();

			//Draw boundingSphereTankTurret
			glPushMatrix();
				glTranslatef(0.0, -12.6, 0.0);
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
				gluSphere(p, boundingSphereTankTurret.radians, 30, 30);
				glDisable(GL_BLEND);
			glPopMatrix();
		glPopMatrix();

		//draw wheels, rotate them with key 7&8
		glPushMatrix();
			glTranslatef(-23.5, -11.0, -57.0);
			for (int i = 0; i < 14; i++) {
				if (i == 7) { //draw the wheels on the opposite side
					glTranslatef(47.0, 0.0, -16.0);
					glRotatef(180.0, 0.0, 1.0, 0.0);
				}
				glPushMatrix();
					if (i > 6) {
						glRotatef(-wheelRot, 1.0, 0.0, 0.0);
					}
					else {
						glRotatef(wheelRot, 1.0, 0.0, 0.0);
					}
					glCallList(tankWheelID);
				glPopMatrix();
				glTranslatef(0.0, 0.0, 16.0);
			}
		glPopMatrix();

		//Draw boundingSphereTankBody
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			gluSphere(p, boundingSphereTankBody.radians, 30, 30);
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(p);

	testIntersect(xProj, yProj, zProj);
	std::cout << "xProj: " << xProj << std::endl;
	std::cout << "yProj: " << yProj << std::endl;
	std::cout << "zProj: " << zProj << std::endl;

}

void drawObj(ObjMesh *pMesh) {
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < int(pMesh->m_iNumberOfFaces); i++) {
		ObjFace *pf = &pMesh->m_aFaces[i];
		for(int j = 0; j < 3; j++) {
			int vk = pf->m_aVertexIndices[j];
			int nk = pf->m_aNormalIndices[j];
			int tk = pf->m_aTexCoordIndicies[j];
			glTexCoord2f(pMesh->m_aTexCoordArray[tk].u, pMesh->m_aTexCoordArray[tk].v);
			glNormal3f(pMesh->m_aNormalArray[nk].x, pMesh->m_aNormalArray[nk].y, pMesh->m_aNormalArray[nk].z);
			glVertex3f(pMesh->m_aVertexArray[vk].x, pMesh->m_aVertexArray[vk].y, pMesh->m_aVertexArray[vk].z);
		}
	}
	glEnd();
}

void testIntersect(float x, float y, float z) {

	if (sqrt(pow(boundingSphereTankBody.position.x - x, 2) + pow(boundingSphereTankBody.position.y - y, 2) + pow(boundingSphereTankBody.position.z - z, 2)) <= boundingSphereTankBody.radians) {
		std::cout << "The point intersects the tank's body" << std::endl;
		if (sqrt(pow(boundingSphereTankTurret.position.x - x, 2) + pow(boundingSphereTankTurret.position.y - 10 - y, 2) + pow(boundingSphereTankTurret.position.z - z, 2)) <= boundingSphereTankTurret.radians) {
			std::cout << "The point intersects the tank's turret" << std::endl;
			if (sqrt(pow(boundingSphereTankMainGun.position.x - 53.7 - x, 2) + pow(boundingSphereTankMainGun.position.y + 102.3 - y, 2) + pow(boundingSphereTankMainGun.position.z + 55.0 - z, 2)) <= boundingSphereTankMainGun.radians) {
				std::cout << "The point intersects the tank's main gun" << std::endl;
			}
			if (sqrt(pow(boundingSphereTankSecondaryGun.position.x - x, 2) + pow(boundingSphereTankSecondaryGun.position.y - y, 2) + pow(boundingSphereTankSecondaryGun.position.z + 11 - z, 2)) <= boundingSphereTankSecondaryGun.radians) {
				std::cout << "The point intersects the tank's secondary gun" << std::endl;
			}
		}
		//if (sqrt(pow(boundingSphereTankWheel.position.x - x,2) + pow(boundingSphereTankWheel.position.y - y,2) + pow(boundingSphereTankWheel.position.z - z,2),2) < boundingSphereTankWheel.radians) {
		//  std::cout << "The point intersects the tank's wheels" << std::endl;
		//} 	
	}
	else {
		std::cout << "The point doesn't intersect with the tank" << std::endl;
	}
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
    case 'q': //zoom out
		zPos--;
		break;
	case 'e': //zoom in
		zPos++;
		break;
	case 'r': //rotate camera left
		yRot+=4;
		break;
	case 'f': //rotate camera right
		yRot-=4; 
		break;
	case 'a': //move camera left
		xPos++; 
		break;
	case 'd': //move camera right
		xPos--; 
		break;
	case 's': //move camera down
		yPos++; 
		break;
	case 'w': //move camera up
		yPos--; 
		break;
	case '1': //rotate turret left
		turretRot+=2;
		break;
	case '2': //rotate turret right
		turretRot-=2;
		break;
	case '3': //move main gun down
		if (mainGunRot > 4)
			break;
		mainGunRot += 1;
		break;
	case '4': //move main gun up
		if (mainGunRot < -4)
			break;
		mainGunRot -= 1;
		break;
	case '5': //rotate secondary gun left
		secondaryGunRot += 2;
		break;
	case '6': //rotate secondary gun right
		secondaryGunRot -= 2;
		break;
	case '7': //rotate wheels left
		wheelRot += 2;
		break;
	case '8': //rotate wheels right
		wheelRot -= 2;
		break;
	case 'y': //move the projectile up
		yProj -= 2;
		break;
	case 'u': //move the projectile down
		yProj += 2;
		break;
	case 'h': //move the projectile left
		xProj += 2;
		break;
	case 'j': //move the projectile right
		xProj -= 2;
		break;
	case 'n': //move the projectile forward
		zProj += 2;
		break;
	case 'm': //move the projectile backward
		zProj -= 2;
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