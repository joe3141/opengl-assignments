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
#include "Vector3f.h"

using namespace std;



Vector3f Vector3f::operator+(Vector3f v) {
	return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f Vector3f::operator-(Vector3f v) {
	return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator*(float n) {
	return Vector3f(x * n, y * n, z * n);
}

Vector3f Vector3f::operator/(float n) {
	return Vector3f(x / n, y / n, z / n);
}

Vector3f Vector3f::unit() {
	return *this / sqrt(x * x + y * y + z * z);
}

Vector3f Vector3f::cross(Vector3f v) {
	return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
