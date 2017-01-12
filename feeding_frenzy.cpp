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

# define M_PI           3.14159265358979323846
# define eps 			10 // Simulates a hitbox
# define winW 			glutGet(GLUT_WINDOW_WIDTH)
# define winH 			glutGet(GLUT_WINDOW_HEIGHT)
# define W 				800
# define H 				600

using namespace std;

void time( int );

/*----- Co-ordinates ----- */

// player
int passX= 500;
int passY= 200;

// chaser
int c1x = 0, c1y = 0;
int c2x = W, c2y = 0;

// target
int t1x = 300, t1y = 400;
int t2x = 500, t2y = 400;

/*------------------------*/

/*----- Angles ----------*/

double angle = 0;

// chaser
double c1angle = 0;
double c2angle = 0;

// target
double t1angle = 0;
double t2angle = 0;

/*------------------------*/

/*-------- Status & misc ----*/

// Game mode choice
bool chosen = false, mode; // mode: false time based, true one shot kill

// Score
int score = 0;

// sync
bool sync = false, ignore = false;

// Finished playing
bool finish = false;

// Time
time_t start, curr;
int secs = 0, mins = 0;

// Power ups
bool ready = false, used = false, which, powered = false; // which: false stun, true double. powered: is being currently used
time_t power_up;

/*------------------------*/

// Initialize

void init(){
	if(!(powered && !which)){ // Don't move the chaser if they're stunned
		c1x = 0, c1y = 0;
		c2x = W, c2y = 0;
	}

	t1x = 300, t1y = 400;
	t2x = 500, t2y = 400;

	angle = 0;

	c1angle = 0;
	c2angle = 0;

	t1angle = 0;
	t2angle = 0;
}

/*----- Utilities ----*/

void displayText(float x, float y, int r, int g, int b, string out) {
	int j = out.length();

	glColor3f( r, g, b );
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, out[i] );
	}
}


// Integer to string/alphanumeric
string itoa(int n){
	string s;
	stringstream out;
	out << n;
	s = out.str();

	return s;
}

/*-----------------*/

/*------ Drawing -------*/

void drawPLayer(){
	glPushMatrix();

	glTranslated(passX, passY, 0);
	glRotated(-90+angle,0,0,1);
	glTranslated(-(winW / 2),-(winH / 2),0);

	glColor3f(0,1,0);

	glBegin(GL_TRIANGLES);

	glVertex3f((winW / 2) - 12.5f, (winH / 2) + 12.5f, 0); // left corner of the roof
	glVertex3f((winW / 2) + 12.5f, (winH / 2) + 12.5f, 0); // right corner of the roof
	glVertex3f((winW / 2), (winH / 2) + 40, 0); // top of the roof

	glEnd();

	glColor3f(1,1,1);

	glBegin(GL_QUADS);

	glVertex3f((winW / 2) - 12.5f, (winH / 2) + 12.5f, 0); // left corner of the roof
	glVertex3f((winW / 2) + 12.5f, (winH / 2) + 12.5f, 0); // right corner of the roof
	glVertex3f((winW / 2) + 12.5f, (winH / 2) - 12.5f, 0); //bottom right corner of the house
    glVertex3f((winW / 2) - 12.5f, (winH / 2) - 12.5f, 0); // bottom left corner of the house

	glEnd();

	glPopMatrix();
}

void drawChaser(int i){
	int cx, cy, cangle;
	glPushMatrix();
	cx = i == 1 ? c1x : c2x;
	cy = i == 1 ? c1y : c2y;
	cangle = i == 1 ? c1angle : c2angle;

	glTranslated(cx, cy, 0);
	glRotated(-90+cangle,0,0,1);
	glTranslated(-20,-50,0);

	glColor3f(1,0,0);

	glBegin(GL_TRIANGLES);

	glVertex3f(20 - 12.5f, 50 + 12.5f, 0); // left corner of the roof
	glVertex3f(20 + 12.5f, 50 + 12.5f, 0); // right corner of the roof
	glVertex3f(20, 50 + 40, 0); // top of the roof

	glEnd();

	glColor3f(0,0,1);

	glBegin(GL_QUADS);

	glVertex3f(20 - 12.5f, 50+ 12.5f, 0); // left corner of the roof
	glVertex3f(20 + 12.5f, 50 + 12.5f, 0); // right corner of the roof
	glVertex3f(20 + 12.5f, 50- 12.5f, 0); //bottom right corner of the house
    glVertex3f(20 - 12.5f, 50 - 12.5f, 0); // bottom left corner of the house

	glEnd();

	glPopMatrix();
}


void drawTarget(int i){
	int tx, ty, tangle;
	glPushMatrix();
	tx = i == 1 ? t1x : t2x;
	ty = i == 1 ? t1y : t2y;
	tangle = i == 1 ? t1angle : t2angle;

	glTranslated(tx, ty, 0);
	glRotated(-90+tangle,0,0,1);
	glTranslated(-300,-400,0);

	glColor3f(0,0,1);

	glBegin(GL_TRIANGLES);

	glVertex3f(300 - 12.5f, 400 + 12.5f, 0); // left corner of the roof
	glVertex3f(300 + 12.5f, 400 + 12.5f, 0); // right corner of the roof
	glVertex3f(300, 400 + 40, 0); // top of the roof

	glEnd();

	glColor3f(1,1,0);

	glBegin(GL_QUADS);

	glVertex3f(300 - 12.5f, 400+ 12.5f, 0); // left corner of the roof
	glVertex3f(300 + 12.5f, 400 + 12.5f, 0); // right corner of the roof
	glVertex3f(300 + 12.5f, 400- 12.5f, 0); //bottom right corner of the house
    glVertex3f(300 - 12.5f, 400 - 12.5f, 0); // bottom left corner of the house

	glEnd();

	glPopMatrix();
}

void displayTime(){
	displayText(725.0, 40, 1, 0, 0, itoa(mins));
	displayText(732.5, 40, 1, 0, 0, ":");
	displayText(735.0, 40, 1, 0, 0, itoa(secs));
}

void mainMenu(){
	displayText(400, 500, 1, 1, 1, "Time based");
	displayText(400, 400, 1, 1, 1, "One shot kill");
	displayText(400, 300, 1, 1, 1, "Exit");
	displayText(400, 200, 1, 0, 0, "ةدراطملا"); // Not working :(
}

void finishScreen(){
	displayText(400, 400, 1, 1, 1, "Game over!");
	displayText(400, 300, 1, 1, 1, "Your score was: ");
	displayText(500, 300, 1, 1, 1, itoa(score));
	displayText(400, 200, 1, 1, 1, "Press ESC to exit");
}


/*-----------------*/


/*--------Calculations---------*/

double getAngle(int x1, int y1, int x2, int y2){
	double deltaX = (double) x1 - x2;
    double deltaY = (double) y1 - y2;

    deltaX = deltaX == 0.0 ? 1.0 : deltaX;

    return atan2(deltaY,deltaX) * 180.0/M_PI;
}

void calcChaseCord(int* cx, int* cy){
	*cx += passX > *cx ? 10 : -10;
	*cy += passY > *cy ? 10 : -10;
	if( c1x - c2x <= eps + 5 && c1y - c2y <= eps + 5)
		c2x = W, c2y = 0;
}

void calcTargetCord(int* tx, int* ty){
	if(*tx >= W || *tx <= 0 || *ty >= H || *ty <= 0){
    	*tx = 400; *ty = 300;
    }else{
		*tx += passX > *tx ? -5 : 5;
		*ty += passY > *ty ? -5 : 5;
	}

	if( t1x - t2x <= eps && t1y - t2y <= eps)
		t2x = 650, t2y = 200;
}

/*------------------------------*/

/*-------Game logic----------*/

// Captured something
bool hasChased(){
	return (abs(t1x - passX) <= eps + 5 && abs(t1y - passY) <= eps + 5)
	|| (abs(t2x - passX) <= eps + 5 && abs(t2y - passY) <= eps + 5);
}

// Got captured
bool isChased(){
	return (abs(c1x - passX) <= eps && abs(c1y - passY) <= eps)
	|| (abs(c2x - passX) <= eps && abs(c2y - passY) <= eps);
}

/*------------------------------*/


void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*------- Main menu ------*/
	if(!chosen)
		mainMenu();
	/*-------------------------*/
	else if (!finish){
		/*------- Player-----------*/
		drawPLayer();
		/*--------------------------*/


		/*------- Chaser-----------*/
		drawChaser(1);
		drawChaser(2);
		/*----------------------------------*/


		/*------- Target-----------*/
		drawTarget(1);
		drawTarget(2);
		/*----------------------------------*/

		/*----- Score, time and power ups ----- */

		// Score
		displayText(755.0, 40.0, 1, 0, 0, itoa(score));

		// Time
		displayTime(); // Starts from 725, ends at 735

		displayText(749.0, 40.0, 1, 1, 1, "|");

		// Power ups
		if(used || !ready){
			displayText(640.0, 40.0, 1, 1, 1, "Stun");
			displayText(668.5, 40.0, 0, 1, 0, "|");
			displayText(674.0, 40.0, 1, 1, 1, "Double");
		}else{
			displayText(640.0, 40.0, 1, 0, 0, "Stun");
			displayText(668.5, 40.0, 0, 1, 0, "|");
			displayText(674.0, 40.0, 1, 0, 0, "Double");
		}

	}else{
		finishScreen();
	}
	/* ------------------------------ */

	glFlush();
	// glutSwapBuffers();
}

void passM(int x,int y){
	if(chosen && !finish){
		/*---------- Player control ----------*/
	    int xReal= (int) round((double)x/(double)winW*W);
	    int yReal= (int) round((double)y/(double)winH*H);

	    angle = getAngle(xReal, H - yReal, passX, passY);

	   	passX=xReal;
		passY=H-yReal;

		/*-----------------------------------*/

		glutPostRedisplay();
	}
}

void actM(int button, int state, int x, int y){

	/*----- Power ups control ----*/
	if(ready && chosen && !finish){
		if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
			which = false; // Stun
			time(&power_up); // timestamp of when the user have chosen the powerup
			powered = true;
		}
		else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
			which = true; // Double score
			time(&power_up); // timestamp of when the user have chosen the powerup
			powered = true;
		}
		used = true;
	}

	/*---------------------------*/
	else if(!chosen && !sync){
		int xReal= (int) round((double)x/(double)winW*W);
		int yReal= (int) round((double)y/(double)winH*H);

		/*-------Mainmenu control----*/

		// Exit
		if(abs(xReal - ((double)(W + 20)/2.0)) <= eps && abs((H - yReal) - ((double)(H + 20)/2.0)) <= eps
			&& button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			exit(0);

		// One shot kill
		else if(abs(xReal - ((double)(W + 70)/2.0)) <= eps + 30 && abs((H - yReal) - ((double)(H + 208)/2.0)) <= eps
			&& button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

			mode = true;
			sync = true;
			glutTimerFunc(0,time,1);
		}

		// Time based
		else if(abs(xReal - ((double)(W + 60)/2.0)) <= eps + 20 && abs((H - yReal) - ((double)(H + 420)/2.0)) <= eps
			&& button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

			mode = false;
			sync = true;
			glutTimerFunc(0,time,1);
		}
	/*---------------------------*/
	}

	// glutPostRedisplay();
}

void key(unsigned char k, int x,int y)
{
	if(k == 27)
		exit(0);
}

void time(int val)
{
	if(val == 1 && ignore) // In case of indeliberate callback duplication.
		return;

	if(chosen && !finish){

		/*----------- Handling time -------*/

		if(val == 1){ // Time to start the game time
			time(&start);
			ignore = true; // make the barrier
		}
		time(&curr);
		int diff = (int) difftime(curr,start);
		secs = diff % 60;
		mins = diff / 60;

		// Time based game mode, 5 mins passed, finish!
		if(mins == 5 && !mode)
			finish = true;
		/* ------------------------------ */

		/*---------- Power ups -----------*/

		// Ready yet?
		ready = !used && secs >= 10;

		// Power up finished?
		if(used && powered){
			time(&curr);
			diff = (int) difftime(curr, power_up);
			powered = diff > 30 ? false : true;
		}

		/* ------------------------------ */

		/*----------Game logic -----------*/

		// Got captured
	    if(isChased()){
			score += which && powered ? -2 : -1;
	    	if(mode) // one shot kill mode, got captured, finish!
	    		finish = true;
	    	Beep(523,180);
	    	init();
	    	glutPostRedisplay();
	    }

	    // Captured a target
	    if(hasChased()){
	    	Beep(900,180);
	    	init();
	    	glutPostRedisplay();
	    	score += which && powered ? 2 : 1;
	    }

	    /* ------------------------------ */

		/*----- Chaser co-ordinates ----- */
	    if(!(powered && !which)){ // Stun chasers
			calcChaseCord(&c1x, &c1y);
			calcChaseCord(&c2x, &c2y);
		}

		/* ------------------------------ */

		/*----- Chaser angle ----- */

	    c1angle = getAngle(passX, passY, c1x, c1y);
	    c2angle = getAngle(passX, passY, c2x, c2y);

		/* ------------------------------ */


		/*----- Target co-ordinates ----- */

	    calcTargetCord(&t1x, &t1y);
	    calcTargetCord(&t2x, &t2y);

		/* ------------------------------ */

		/*----- Target angle ----- */

		t1angle = getAngle(passX, passY, t1x, t1y) + 180;
		t2angle = getAngle(passX, passY, t2x, t2y) + 180;

		/* ------------------------------ */

		/*----- Score ----- */

		displayText(750.0, 40.0, 1, 0, 0, itoa(score));

		/* ------------------------------ */

		glutPostRedisplay();
		glutTimerFunc(20,time,0);
	}else if(sync){
		chosen = true;
		sync = false;
		glutPostRedisplay();
		glutTimerFunc(0,time,1);
	}else{
		glutTimerFunc(0,time,1); // keep sending "1" since the game hasn't started yet
	}
}

int main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(W, H);
	//glutInitWindowPosition(150, 150);


	glutCreateWindow("The Chase");
	glMatrixMode(GL_PROJECTION);
	glutDisplayFunc(Display);
	glutPassiveMotionFunc(passM);
	glutMouseFunc(actM);
	glutKeyboardFunc(key);
	glLoadIdentity();
	// glutSetCursor(GLUT_CURSOR_NONE);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, W, 0.0, H);
	glutFullScreen();
	glutTimerFunc(0,time,1);	// Send "1" to the callback func argument to indicate that the game hasn't started yet

	glutMainLoop();
	return 0;
}

