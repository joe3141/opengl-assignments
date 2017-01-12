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
#include "planet.h"
#include "moon.h"

void Planet::draw(){
	GLUquadricObj* sphere = gluNewQuadric();							
	gluQuadricNormals(sphere, GLU_SMOOTH);		
	gluQuadricTexture(sphere, GL_TRUE);			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glRotatef( inclination, 0.0, 0.0, 1.0);
				glRotatef( 360.0 * (currDay/orbitDur), 0.0, 1.0, 0.0);
				glTranslatef(distance, 0.0, 0.0 );
				glRotatef( 360.0 * (earthDaysPassed/rotDur), 0.0, 1.0, 0.0 );
				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, tex);
				gluSphere(sphere, radius, 15, 15);
			glPopMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(sphere);
}
