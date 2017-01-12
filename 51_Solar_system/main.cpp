/*#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif*/

#include <windows.h>
#include <GL/gl.h>
// Opengl includes. Not sure How it works in visual studio. I'm using codeblocks
#include <GL/glu.h>
#include <GL/glu_.h>

#include <GL/glut.h>


#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include "Vector3f.h"
#include "camera.h"
#include "moon.h"
#include "planet.h"
#include "sun.h"
#include "utils.h"
#include "RGBpixmap.h"

#include "MMSystem.h"


using namespace std;


/*------Global variables------*/
Camera camera;
int oldX = 0, oldY = 0;
GLuint skyBoxTex = 12;
Sun sun;
bool pause = false;
bool s = true, e = false;
/*----------------------------*/

void drawStarBox();

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };

	// GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	GLfloat lightPosition[] = { 1.0f, 0, 0, 0.0f };
	GLfloat lightPosition1[] = { -1.0f, 0, 0, 0.0f };

	GLfloat lightPosition2[] = { 0, 0, 0, 1.0f };
	GLfloat lightPosition3[] = { 0, 0, 0, -1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPosition3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, W / H, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}



void Display(){
	setupLights();
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	//glEnable ( GL_TEXTURE_2D );
   	//glBindTexture ( GL_TEXTURE_2D, EarthTexture);
   	glMatrixMode(GL_MODELVIEW);
   // glLoadIdentity();
   	glPushMatrix();
   		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   		glPushMatrix();
   			// drawStarBox();
   		glPopMatrix();
   	glPopMatrix();

	glPushMatrix();

		sun.draw();

	glPopMatrix();




	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	// float d = 0.05;
	float d = 1;

	switch (key) {
	case 'w':
	if(camera.eye.z > -SKY_BOX_RADIUS)
		camera.moveZ(d);
		break;
	case 's':
	if(camera.eye.z < SKY_BOX_RADIUS)
		camera.moveZ(-d);
		break;
	case 'a':
	if(camera.eye.x > -SKY_BOX_RADIUS)
		camera.moveX(d);
		break;
	case 'd':
	if(camera.eye.x < SKY_BOX_RADIUS)
		camera.moveX(-d);
		break;
	case 'm':
		Moon::speed+=d;
		break;
	case 'n':
		Moon::speed-=d;
		break;

	case'p':
		pause = !pause;
		break;

	case 27:
		exit(EXIT_SUCCESS);
	}
	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void passM(int x, int y){
	float a = 1.0;

	if(abs(x - oldX) > abs((H - y) - oldY)){

		if(x  > oldX)
			camera.rotateY(-a);
		else
			camera.rotateY(a);

	}else{

		if((H - y) > oldY)
			camera.rotateX(a);
		else
			camera.rotateX(-a);
	}


	oldX = x;
	oldY = H - y;

	glutPostRedisplay();
}

void time(int val){

	// if(val == 1)
	// 	camera.moveZ((-0.05) * 40);
	if(!pause){
		sun.update();

		Moon::updateDays();
	}
	if((camera.eye.x >= EARTH_ORBIT_RADIUS || camera.eye.x <= -EARTH_ORBIT_RADIUS) ||
		(camera.eye.y >= EARTH_ORBIT_RADIUS || camera.eye.y <= -EARTH_ORBIT_RADIUS) ||
		(camera.eye.z >= EARTH_ORBIT_RADIUS || camera.eye.z <= -EARTH_ORBIT_RADIUS)){
		if(!e){
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("assets/sounds/earth.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
			e = true;
			s = false;
		}
	}
	else{
		if(!s){
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("assets/sounds/sun.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
			e = false;
			s = true;
		}
	}
	printf("%f, %f, %f, %f, %f, %f, %f, %f, %f\n", camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x,
		camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
	glutPostRedisplay();
	glutTimerFunc(10,time,0);
}

void drawStarBox(){
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	// glTranslated(50,0,0);
	glRotated(90,1,0,1);
	glBindTexture(GL_TEXTURE_2D, skyBoxTex);
	gluSphere(qobj,SKY_BOX_RADIUS,15,15);
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(qobj);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Solar System Simulation");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutPassiveMotionFunc(passM);
	glutSpecialFunc(Special);
	// earth = gluNewQuadric();
 //  	gluQuadricTexture( earth, GL_TRUE);
	glutTimerFunc(0,time,1);

	// initPlanets();
	// loadImages();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
	sun = Sun(SUN_RADIUS, -1.0f);
	RGBpixmap pix;
	pix.readBMPFile("assets/pics/skymap.bmp", false);
	pix.setTexture(skyBoxTex);
	// camera.moveZ((-0.05) * 4);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutMainLoop();
	return 0;
}

