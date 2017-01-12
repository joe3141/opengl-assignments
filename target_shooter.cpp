#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <gl/gl.h> // Opengl includes. Not sure How it works in visual studio. I'm using codeblocks
#include <GL/glu.h>
#include <GL/glu_.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;


/*
To play, choose the weapon using the "1", "2" & "3" buttons
Then press M to fire, press I if you want to play again, otherwise press ESC
I apologize for the messy code, it's not modular at all, but I was in a bit of a hurry
I apologize again :D
Regards.
*/

double bangle = 0;

double bdelta = 0;

float t_gren = 0.0, t_shur = 0.0;

double gx = 0.0, gz = 0.0, tx = 0.0, tz = 0.0, wangle = 0.0, targetz = 0;

int readyx = 0, readyy = 0;

int traj = 0;

bool bmoving = false, smoving = false, bbmoving = false, bvis = true, gvis = false, svis = false, fired = false, replay = false;
 int done = 0;


#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

double* bezier(float t_gren, int* p0,int* p1,int* p2,int* p3)
{
	double res[2];
	res[0]= (double) pow((1-t_gren),3)*p0[0]+3*t_gren*pow((1-t_gren),2)*p1[0]+3*pow(t_gren,2)*(1-t_gren)*p2[0]+pow(t_gren,3)*p3[0];
	res[1]= (double) pow((1-t_gren),3)*p0[1]+3*t_gren*pow((1-t_gren),2)*p1[1]+3*pow(t_gren,2)*(1-t_gren)*p2[1]+pow(t_gren,3)*p3[1];
	return res;
}

void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int) strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};



class Camera {
public:
	Vector3f eye, center, up;

	// 1, 1, 1, 0, 0, 0, 0, 1, 0
	// eyeY = 0.061058f
	// centerY = 0.074547f

	//0.950753 0.082139 0.502582
	//-0.049009 0.093628 0.485461
	// 0.013519 0.999907 -0.001588
	Camera(float eyeX = 0.950753, float eyeY = 0.082139, float eyeZ = 0.502582, float centerX = -0.049009, float centerY = 0.093628, float centerZ = 0.485461, float upX = 0.013519, float upY = 0.999907, float upZ = -0.001588) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void init(){
		eye = Vector3f(0.950753, 0.082139, 0.502582);
		center = Vector3f(-0.049009, 0.093628, 0.485461);
		up = Vector3f(0.013519, 0.999907, -0.001588);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
		print();
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
		print();
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
		print();
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
		print();
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
		print();
	}

	void look() {

		// 0.870770, 0.061058, 0.501212
		// -0.128992, 0.074547, 0.484091
		// 0.013519, 0.999907, -0.001588

		// right
		// -0.099522, 0.073792, 0.259612

		// left
		// -0.074547, 0.074356, 0.827093

		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}

	void print(){
		// printf("/------------/\n%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n/--------------/\n", eye.x, eye.y, eye.z,
		// 	center.x, center.y, center.z,
		// 	up.x, up.y, up.z);
	}
};

Camera camera;


void init(){

	bangle = 0;

	bdelta = 0;

	t_gren = 0.0, t_shur = 0.0;

	gx = 0.0, gz = 0.0, tx = 0.0, tz = 0.0, wangle = 0.0, targetz = 0;

	readyx = 0, readyy = 0;

	bmoving = false, smoving = false, bbmoving = false,  fired = false;

	camera.init();
}

void pinit(){
	bangle = 0;

	bdelta = 0;

	t_gren = 0.0, t_shur = 0.0;

	gx = 0.0, gz = 0.0, tx = 0.0, tz = 0.0;
	bmoving = false, smoving = false, bbmoving = false,  fired = false;
	readyx = 0, readyy = 0;
}
void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

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
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void drawWalls(){
	glColor3f(1, 0, 0);
	drawWall(0.02);

	glPushMatrix();
		glRotated(90, 0, 0, 1.0);
		glColor3f(0, 1, 0);
		drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
		glRotated(-90, 1.0, 0.0, 0.0);
		glColor3f(1, 1, 0);
		drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
		glTranslated(1.0, 1.0, 0.0);
		glRotated(-90, 0.0, 1.0, 0.0);
		glColor3f(1, 0, 1);
		drawWall(0.02);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0.0, 0.0, 1.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		glColor3f(1, 1, 0);
		drawWall(0.02);
	glPopMatrix();
}

void drawTarget(){

	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glPushMatrix();
	glTranslated(0, -0.15, -0.015);
		glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslated(0.01,0.25,0.5);
			glRotated(-90, 0, 1, 0);
			glRotated(90, 0, 0, 1);
			// glutSolidCone(0.2, 0.5, 10, 8);
			gluDisk( qobj, 0.1, 0.11, 15, 15);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslated(0.03,0.25,0.5);
			glRotated(-90, 0, 1, 0);
			glRotated(90, 0, 0, 1);
			// glutSolidCone(0.1, 0.5, 10, 8);
			gluDisk( qobj, 0.04, 0.05, 15, 15);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslated(0.03,0.25,0.5);
			glRotated(-90, 0, 1, 0);
			glRotated(90, 0, 0, 1);
			glutSolidSphere(0.005, 10, 10);
		glPopMatrix();
	glPopMatrix();
}

void drawBullet(){
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();

	// gluQuadricDrawStyle(qobj,GLU_LINE);
	gluQuadricDrawStyle(qobj,GLU_FILL);

	glPushMatrix();
	// glTranslated(2,0.07,0.5);
	glTranslated(0.8,0.1,0.426);
	glScaled(0.03, 0.03, 0.03);
	glRotated(-90, 0, 1, 0);
		glTranslated(2,0.07,0);
		glRotated(bangle,0,0,1);
		glTranslated(-2,-0.07,0);
		glPushMatrix();
			glColor3f(0.5, 0.5, 0.5);
			glTranslated(2,0.07,0.5);
			gluCylinder(qobj, 0.1, 0.1, 0.4, 15,15);
		glPopMatrix();


		glPushMatrix();
			// glColor3f(1, 0, 0);
			glTranslated(2,0.07,0.5);
			gluDisk( qobj, 0.0005, 0.11, 15, 15);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.8, 0.8, 0.8);
			glTranslated(2,0.07,0.4999f);
			gluDisk( qobj, 0.04, 0.08, 30, 30);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.5, 0.5, 0.5);
			glTranslated(2,0.07,0.9f);
			gluCylinder(qobj, 0.1, 0.08, 0.1, 15,15);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.5, 0.5, 0.5);
			glTranslated(2,0.07,1.0f);
			gluCylinder(qobj, 0.08, 0.08, 0.2, 15,15);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.5, 0.5, 0.5);
			glTranslated(2,0.07,1.2f);
			gluCylinder(qobj, 0.08, 0.0001, 0.2, 15,15);
		glPopMatrix();

	glPopMatrix();
}

void drawGrenade(){
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();

	gluQuadricDrawStyle(qobj,GLU_FILL);

	glPushMatrix();

		glColor3f(0.2, 0.3, 0.4);
		glTranslated(0.8,0.05,0.49);
		glRotated(bangle,1,0,1);
		glutSolidSphere(0.005, 15, 15);

		glPushMatrix();
			glTranslated(0,0.006,0);
			glRotated(90, 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glColor3f(0.7, 0.7, 0.7);
			gluCylinder(qobj, 0.003, 0.003, 0.004, 15,15);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0,0.006,0);
			glRotated(90, 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glColor3f(1, 1, 1);
			gluDisk( qobj, 0, 0.003, 15, 15);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0,0.001,0);
			glRotated(90, 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glColor3f(1, 1, 1);
			//gluDisk( qobj, 0.001, 0.006, 15, 15);
			glutSolidTorus(0.0005,0.005,10,10);
		glPopMatrix();

	glPopMatrix();
}

void drawShurikenBlade(){
	glPushMatrix();
		glTranslated(0, -0.0034, 0);
		glScaled(1, 4, 1);
		glPushMatrix();
			glColor3f(0.7, 0.7, 0.7);
			// glTranslated(0, 0, -0.003);
			glTranslated(-0.02, 0, 0.0102);
			glRotated(90, 0, 1, 0);
			glPushMatrix();
				glTranslated(0, 0.0008, 0.02);
				glScaled(2.2f, 0.04f, 0.83);
				// glRotated(45, 0, 0, 1);
				glRotated(-90, 0, 1, 0);
				glutSolidCone(0.002, 0.0027, 10, 8);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, 0.0008, 0.01);
			glRotated(-45, 0, 1, 0);
			glColor3f(0.5, 0.5, 0.5);
			glScaled(0.6, 0.01f, 0.6);
			glutSolidCube(0.004);
		glPopMatrix();
	glPopMatrix();

}

void drawShuriken(){
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj,GLU_FILL);

	glPushMatrix();
		glTranslated(0.8,0.1,0.53);
		glRotated(bangle, 0, 1, 0);
		glPushMatrix();
			glRotated(90, 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glColor3f(0.6,0.6, 0.6);
			glScaled(0.009, 0.009, 0.009);
			glutSolidTorus(0.08, 0.3, 10,10);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1, 0.843f, 0);
			glTranslated(0, 0.0008, 0);
			glRotated(90, 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glutSolidCone(0.002, 0.004, 10, 8);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, 0.0008, 0);
			glRotated(-90, 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glutSolidCone(0.002, 0.0027, 10, 8);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0.006, 0, 0);
			glRotated(-90, 0, 1, 0);
			drawShurikenBlade();
		glPopMatrix();


		glPushMatrix();
			glTranslated(-0.002, 0, -0.005);
			glRotated(30, 0, 1, 0);
			drawShurikenBlade();
		glPopMatrix();

		glPushMatrix();
			glTranslated(-0.002, 0, 0.0045);
			glRotated(150, 0, 1, 0);
			drawShurikenBlade();
		glPopMatrix();

	glPopMatrix();
}

void Display() {
	setupCamera();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawWalls();
	glPushMatrix();
	glTranslated(0, 0, targetz);
	drawTarget();
	glPopMatrix();

	glPushMatrix();

	glTranslated(0, 0, wangle);

	glPushMatrix();
	glTranslated(bdelta, 0, 0);
	if(bvis)
	drawBullet();
	glPopMatrix();

	//0,0
	//200, 180,
	//300 180
	//500 0
	glPushMatrix();
	glTranslated(gz,gx,0);
	if(gvis)
	drawGrenade();
	glPopMatrix();

	glPushMatrix();
	glTranslated(tx,0,tz);
	if(svis)
	drawShuriken();
	glPopMatrix();

	if(done == 2){
		glScaled(1, 1, 10);
		print(320, 240, "Press i to play again!");
	}

	glPopMatrix();

	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	// float d = 0.01;

	float d = 0.01;

	switch (key) {
	case 'w':
		// camera.moveY(d);
		break;
	case 's':
		// camera.moveY(-d);
		break;
	case 'a':
		// camera.moveX(d);
		targetz = targetz >= 0.37 ? targetz : targetz + 0.01;
		// printf("%f\n", targetz);
		break;
	case 'd':
		// camera.moveX(-d);
		targetz = targetz <= -0.37 ? targetz : targetz - 0.01;
		// printf("%f\n", targetz);
		break;
	case 'q':
		// camera.moveZ(d);
		break;
	case 'e':
		// camera.moveZ(-d);
		break;
	case 'r':
		// ready = true;
		// readyx = x;
		// readyy = 480 - y;
		printf("------------\n%d, %d\n-----------\n", x, 480-x);
		break;
	case 'm':
			// init();
			bmoving = true;
			smoving = true;
			bbmoving = true;
			fired = true;
		break;
	case '1':
		bvis = true, svis = false, gvis = false;
		traj = 0;
		break;
	case '2':
		bvis = false, svis = true, gvis = false;
		traj = 2;
		break;
	case '3':
		bvis = false, svis = false, gvis = true;
		traj = 1;
		break;
	case 'i':
		init();
		camera.init();
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	// float a = 1.0;
	float a = 2.0;
	switch (key) {
	case GLUT_KEY_UP:
		// camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		// camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		if(wangle < 0.47)
		camera.moveX(0.01);
		wangle = wangle >=0.47 ? wangle : wangle + 0.01;
		break;
	case GLUT_KEY_RIGHT:
		if(wangle > -0.47)
		camera.moveX(-0.01);
		wangle = wangle <= -0.47 ? wangle : wangle - 0.01;
		break;
	}

	glutPostRedisplay();
}

	//0,0
	//200, 180,
	//300 180
	//500 0

void time(int val){

	if(traj == 0 && !bbmoving && fired){
		pinit(); // this makes fired = false
		replay = true;
		bbmoving = true;
		done = 1;
	}
	if(traj == 1 && !bmoving && fired){
		pinit();
		gvis = true;
		bvis = false;
		replay = true;
		bmoving = true;
		done = 1;
	}
	if(traj == 2 && !smoving && fired){
		pinit();
		svis = true;
		bvis = false;
		replay = true;
		smoving = true;
		done = 1;
	}


	bangle = bmoving || smoving || bbmoving ? 1 + bangle : 0;
	bdelta = bbmoving ? -0.01 + bdelta : bdelta;
	if(bdelta < -0.75){
		bdelta = -0.75;
		bbmoving = false;
		replay = false;
		done = 2;
	}

	t_gren = bmoving ? 0.01 + t_gren : 0;
	if(t_gren>1.5)
		t_gren=1.5;

	t_shur = smoving ? 0.01 + t_shur : 0;
	if(t_shur>1.668){
		t_shur= 1.668;
		smoving = false;
		replay = false;
		done = 2;
	}
	glutWarpPointer(640 / 2, 480 / 2);

	double gren[2];
	double shur[2];

	int p0[2] = {0,0};
	int p1[2] = {200, 180};
	int p2[2] = {300, 180};
	int p3[2] = {500, 0};

	int s0[2] = {100, 100};
	int s1[2] = {300, 190};
	int s2[2] = {640, 435};
	int s3[2] = {650, 185};

	gren[0]=  pow((1-t_gren),3)*p0[0]+3*t_gren*pow((1-t_gren),2)*p1[0]+3*pow(t_gren,2)*(1-t_gren)*p2[0]+pow(t_gren,3)*p3[0];
	gren[1]=  pow((1-t_gren),3)*p0[1]+3*t_gren*pow((1-t_gren),2)*p1[1]+3*pow(t_gren,2)*(1-t_gren)*p2[1]+pow(t_gren,3)*p3[1];

	shur[0]=  pow((1-t_shur),3)*s0[0]+3*t_shur*pow((1-t_shur),2)*s1[0]+3*pow(t_shur,2)*(1-t_shur)*s2[0]+pow(t_shur,3)*s3[0];
	shur[1]=  pow((1-t_shur),3)*s0[1]+3*t_shur*pow((1-t_shur),2)*s1[1]+3*pow(t_shur,2)*(1-t_shur)*s2[1]+pow(t_shur,3)*s3[1];

	if(gz < -0.786 && gx > 0.05){
		bmoving = false;
		replay = false;
		done = 2;
	}
	double tzOld = tz, txOld = tx;
	// gren = bezier(t_gren, p0, p1, p2, p3);
	gz = bmoving ? (-(gren[0]/500.0f)*0.2)-0.52 : gz; gx = bmoving ? ((gren[1]/500.0f)*0.2)+0.126 : gx;
	tz = smoving ? -((shur[0]/500.0f)*0.2) : tz; tx = smoving ? ((shur[1]/500.0f)*0.2) - 0.3 : tx;


	if(replay && traj == 0)
		camera.moveZ(0.01);

	if(replay && traj == 1){
		camera.moveZ(0.007);
	}

	if(replay && traj == 2){
		if(tx > txOld)
			camera.moveZ(0.007);
		else
			camera.moveZ(-0.001);
		if(tz > tzOld)
			camera.moveX(0.003);
		else
			camera.moveX(-0.003);
	}


	// printf("%d", replay);
	glutPostRedisplay();
	glutTimerFunc(10,time,0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("FPS TEST");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(0,time,1);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	// glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(640 / 2, 480 / 2);

	glutMainLoop();

	return 0;
}
