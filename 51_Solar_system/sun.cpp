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
#include "sun.h"
#include "planet.h"
#include "utils.h"
#include "moon.h"

void Sun::draw(){
	GLUquadric *sphere = gluNewQuadric();
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			// glColor3f(1,1,0);
			glRotated(angle, 0, 1.0, 0);
			glRotatef( -90.0, 1.0, 0, 0);
			glBindTexture(GL_TEXTURE_2D, tex);
			gluSphere(sphere, radius, 15, 15);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(sphere);



	for(int i = 0; i < 9; ++i){
		children[i].draw();
		if(i == 5){
			GLUquadricObj* sphere = gluNewQuadric();
			gluQuadricNormals(sphere, GLU_SMOOTH);
			gluQuadricTexture(sphere, GL_TRUE);
			glEnable(GL_TEXTURE_2D);
				glPushMatrix();
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glPushMatrix();
						glRotatef(SATURN_INCLINATION, 0.0, 0.0, 1.0);
						glRotatef( 360.0 * (Moon::currDay/SATURN_ORBIT_DUR), 0.0, 1.0, 0.0);
						glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0 );
						glRotatef( -90.0, 1.0, 0.0, 0.0 );
						glBindTexture(GL_TEXTURE_2D, RingTexture);
						glScalef(1,1,.02);
						gluSphere(sphere, SATURN_RADIUS*2, 48, 48);
					glPopMatrix();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			gluDeleteQuadric(sphere);
		}

		if(i == 0){
			float MoonRevolution = Moon::currDay / 30.0f;
			GLUquadricObj* sphere = gluNewQuadric();
			gluQuadricNormals(sphere, GLU_SMOOTH);
			gluQuadricTexture(sphere, GL_TRUE);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glPushMatrix();
						glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
						glRotatef( 360.0 * (Moon::currDay/EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
						glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0 );
						glRotatef( 360.0 * MoonRevolution, 0.0, 1.0, 0.0 );
						glTranslatef( MOON_ORBIT_RADIUS  , 0.0, 0.0 );
						glBindTexture(GL_TEXTURE_2D, MoonTexture);
						gluSphere(sphere, MOON_RADIUS, 48, 48);
					glPopMatrix();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);
			gluDeleteQuadric(sphere);
		}
		// }else{
		// 	int n = getRandom(0, 2);
		// 	for(int i = 0; i <n; ++i){
		// 		float MoonRevolution = Moon::currDay / fRand(20.0f, 50.0f);
		// 		GLUquadricObj* sphere = gluNewQuadric();
		// 		gluQuadricNormals(sphere, GLU_SMOOTH);
		// 		gluQuadricTexture(sphere, GL_TRUE);
		// 		glEnable(GL_TEXTURE_2D);
		// 		glPushMatrix();
		// 				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		// 				glPushMatrix();
		// 					glRotatef(children[i].inclination, 0.0, 0.0, 1.0);
		// 					glRotatef( 360.0 * (Moon::currDay/children[i].orbitDur)/5.0, 0.0, 1.0, 0.0);
		// 					glTranslatef(children[i].distance, 0.0, 0.0 );
		// 					glRotatef( 360.0 * MoonRevolution/5.0, 0.0, 1.0, 0.0 );
		// 					glTranslatef(fRand(MOON_ORBIT_RADIUS/3.0, MOON_ORBIT_RADIUS ) , 0.0, 0.0 );
		// 					glBindTexture(GL_TEXTURE_2D, MoonTexture);
		// 					gluSphere(sphere, fRand(MOON_RADIUS/2.0, 2.0 * MOON_RADIUS), 48, 48);
		// 				glPopMatrix();
		// 			glPopMatrix();
		// 		glDisable(GL_TEXTURE_2D);
		// 		gluDeleteQuadric(sphere);
		// 	}
		// }
	}
}

void Sun::update(){
	angle += speed;
}

// void Sun::initPlanets(){
// 	float r = radius / 2.0;
// 	for(int i = 0; i < 9; ++i){
// 		float d = fRand((radius + r), 2.0 * (radius + r));
// 		float s = fRand(-1.0, 1.0);

// 		Planet p(r, d, s, 0);
// 		children[i] = p;
// 	}
//}

	void Sun::initPlanets(){
		loadImages();

		children[0] = Planet(EARTH_RADIUS, EARTH_ORBIT_RADIUS, 0, EarthTexture, EARTH_INCLINATION, EARTH_ORBIT_DUR, EARTH_ROTATION_DUR);
		children[1] = Planet(MERCURY_RADIUS, MERCURY_ORBIT_RADIUS, 0, MercuryTexture, MERCURY_INCLINATION, MERCURY_ORBIT_DUR, MERCURY_ROTATION_DUR);
		children[2] = Planet(VENUS_RADIUS, VENUS_ORBIT_RADIUS, 0, VenusTexture, VENUS_INCLINATION, VENUS_ORBIT_DUR, VENUS_ROTATION_DUR);
		children[3] = Planet(MARS_RADIUS, MARS_ORBIT_RADIUS, 0, MarsTexture, MARS_INCLINATION, MARS_ORBIT_DUR, MARS_ROTATION_DUR);
		children[4] = Planet(JUPITER_RADIUS, JUPITER_ORBIT_RADIUS, 0, JupiterTexture, JUPITER_INCLINATION, JUPITER_ORBIT_DUR, JUPITER_ROTATION_DUR);
		children[5] = Planet(SATURN_RADIUS, SATURN_ORBIT_RADIUS, 0, SaturnTexture, SATURN_INCLINATION, SATURN_ORBIT_DUR, SATURN_ROTATION_DUR);
		children[6] = Planet(URANUS_RADIUS, URANUS_ORBIT_RADIUS, 0, UranusTexture, URANUS_INCLINATION, URANUS_ORBIT_DUR, URANUS_ROTATION_DUR);
		children[7] = Planet(NEPTUNE_RADIUS, NEPTUNE_ORBIT_RADIUS, 0, NeptuneTexture, NEPTUNE_INCLINATION, NEPTUNE_ORBIT_DUR, NEPTUNE_ROTATION_DUR);
		children[8] = Planet(PLUTO_RADIUS, PLUTO_ORBIT_RADIUS, 0, PlutoTexture, PLUTO_INCLINATION, PLUTO_ORBIT_DUR, PLUTO_ROTATION_DUR);
	}

	void Sun::loadImage(string filename, GLuint &text){
		RGBpixmap pix;
		pix.readBMPFile(filename, false);
		pix.setTexture(text);
	}

	void Sun::loadImages(){
		loadImage(EARTH_BMP_FILENAME, EarthTexture);
		loadImage(MOON_BMP_FILENAME, MoonTexture);
		loadImage(SUN_BMP_FILENAME,	SunTexture);
		loadImage(MERCURY_BMP_FILENAME, MercuryTexture);
		loadImage(VENUS_BMP_FILENAME, VenusTexture);
		loadImage(MARS_BMP_FILENAME, MarsTexture);
		loadImage(JUPITER_BMP_FILENAME, JupiterTexture);
		loadImage(SATURN_BMP_FILENAME, SaturnTexture);
		loadImage(URANUS_BMP_FILENAME, UranusTexture);
		loadImage(NEPTUNE_BMP_FILENAME, NeptuneTexture);
		loadImage(PLUTO_BMP_FILENAME, PlutoTexture);
		loadImage(RING_BMP_FILENAME, RingTexture);
	}


