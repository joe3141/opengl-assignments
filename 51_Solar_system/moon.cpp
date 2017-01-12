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
#include "moon.h"
#include "utils.h"

float Moon::earthDaysPassed = 0.0, Moon::currDay = 0.0, Moon::speed = 0.01;

void Moon::draw(){
	glPushMatrix();
	//glTranslated(v.x, v.y, v.z);
	//glRotated(angle, 0, 1.0, 0);
	glutSolidSphere(radius, 15, 15);

	glPopMatrix();
}

void Moon::updateDays(){
	earthDaysPassed += speed;
	// currDay = fmod((currDay + speed) , 366.0f);
	currDay += speed;
	if(currDay == 365.0f)
		currDay = 0.0f;
}

void changeSpeed(float newSpeed){
	Moon::speed = newSpeed;
}
