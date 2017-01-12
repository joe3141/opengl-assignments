#ifndef MOON_H
#define  MOON_H

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
#include "body.h"
#include "utils.h"
#include "Vector3f.h"

class Moon : public Body
{

	

public:
	float  distance, inclination, orbitDur, rotDur;
	static float earthDaysPassed, currDay, speed;
	GLuint tex;

	Moon()
	: Body()
	{
	}

	Moon(float r, float d, GLuint t, float i, float orbD, float rotD)
	: Body(r), distance(d), inclination(i), orbitDur(orbD), rotDur(rotD), tex(t)
	{
	}

	static void updateDays();
	static void changeSpeed();

	virtual void draw();
};

#endif
