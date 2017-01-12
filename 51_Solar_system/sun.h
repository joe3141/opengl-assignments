#ifndef SUN_H
#define  SUN_H

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
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include "body.h"
#include "planet.h"
#include "utils.h"
#include "Vector3f.h"
#include "RGBpixmap.h"

using namespace std;

class Sun : public Body
{

private:

	Planet children[9]; // I know it's 8 children, but pluto is a "dwarf" planet which makes it very similar to one

	GLuint EarthTexture = 0;
	GLuint MoonTexture  = 1;
	GLuint SunTexture   = 2;
	GLuint MercuryTexture = 3;
	GLuint VenusTexture = 4;
	GLuint MarsTexture = 5;
	GLuint JupiterTexture = 6;
	GLuint SaturnTexture = 7;
	GLuint UranusTexture = 8;
	GLuint NeptuneTexture = 9;
	GLuint PlutoTexture = 10;
	GLuint RingTexture = 11;


	void loadImage(string filename, GLuint &text);
	void loadImages();

	void initPlanets();

public:
	float speed, angle;
    GLuint tex;
    Sun(){
    }

	Sun(float r, float s)
	: Body(r), speed(s)
	{
		this->angle = getRandom(0, 2 * M_PI);
		initPlanets();
		tex = SunTexture;
	}

	virtual void draw();
	void update();
};

#endif
