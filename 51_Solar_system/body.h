#ifndef BODY_H
#define  BODY_H

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

class Body
{
public:
	float radius;

	Body(){}

	Body(float r)
	: radius(r)
	{
	}

	virtual void draw(){};
};

#endif
