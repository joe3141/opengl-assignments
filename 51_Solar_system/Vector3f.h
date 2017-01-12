#ifndef VECTOR3F_H
#define  VECTOR3F_H

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

#include "utils.h"


class Vector3f
{

public:
	float x, y, z;

	Vector3f(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(){
		x = fRand(0.0, 5.0);
		y = fRand(0.0, 5.0);
		z = fRand(0.0, 5.0);
	}

	Vector3f operator+(Vector3f v);
	Vector3f operator-(Vector3f v);
	Vector3f operator*(float n);
	Vector3f operator/(float n);

	Vector3f cross(Vector3f v);
	Vector3f unit();
};

#endif