#ifndef PLANET_H
#define  PLANET_H

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
#include "Vector3f.h"

class Planet : public Moon
{

private:
	void initMoons(){};
public:
	int numMoons;
	Moon children[9];

	Planet()
	: Moon()
	{

	}

	Planet(float r, float d, int n, GLuint t, float i, float orbD, float rotD)
	: Moon(r, d, t, i, orbD, rotD), numMoons(n)
	{
		initMoons();
	}

	virtual void draw();
};

#endif
