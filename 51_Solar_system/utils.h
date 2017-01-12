#ifndef UTILS_H
#define UTILS_H

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

# define M_PI           3.14159265358979323846
# define eps 			10 // Simulates a hitbox
# define W 				800
# define H 				600
# define winW 			glutGet(GLUT_WINDOW_WIDTH)
# define winH 			glutGet(GLUT_WINDOW_HEIGHT)
# define DEG2RAD(a) 	((a) * ((M_PI) / (180.0)))
# define RAD2DEG(a)		((a) * ((180.0) / (M_PI)))

inline double* bezier(float t_gren, int* p0,int* p1,int* p2,int* p3)
{
	double res[2];
	res[0]= (double) pow((1-t_gren),3)*p0[0]+3*t_gren*pow((1-t_gren),2)*p1[0]+3*pow(t_gren,2)*(1-t_gren)*p2[0]+pow(t_gren,3)*p3[0];
	res[1]= (double) pow((1-t_gren),3)*p0[1]+3*t_gren*pow((1-t_gren),2)*p1[1]+3*pow(t_gren,2)*(1-t_gren)*p2[1]+pow(t_gren,3)*p3[1];
	return res;
}

inline int getRandom(int min,int max){
        return int(min + (rand() % (int)(max - min + 1)));
}

inline double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

const char MERCURY_BMP_FILENAME[] =	"assets/pics/mercurymap.bmp";
const char VENUS_BMP_FILENAME[] = 	"assets/pics/venusmap.bmp";
const char MARS_BMP_FILENAME[] = 		"assets/pics/marsmap.bmp";
const char JUPITER_BMP_FILENAME[] = "assets/pics/jupitermap.bmp";
const char SATURN_BMP_FILENAME[] = 	"assets/pics/saturnmap.bmp";
const char URANUS_BMP_FILENAME[] = 	"assets/pics/uranusmap.bmp";
const char NEPTUNE_BMP_FILENAME[] = "assets/pics/neptunemap.bmp";
const char PLUTO_BMP_FILENAME[] = 	"assets/pics/plutomap.bmp";
const char RING_BMP_FILENAME[] = 		"assets/pics/saturnringmap.bmp";
const char SUN_BMP_FILENAME[]= 		"assets/pics/sunmap.bmp";
const char EARTH_BMP_FILENAME[] = "assets/pics/earthmap.bmp";
const char MOON_BMP_FILENAME[] = "assets/pics/moonmap.bmp";


const float EARTH_RADIUS = 0.18;
const float MOON_RADIUS = 0.04;
const float MERCURY_RADIUS = 0.1;
const float VENUS_RADIUS = 0.18;
const float MARS_RADIUS = 0.3;
const float JUPITER_RADIUS = 0.6;
const float SATURN_RADIUS = 0.5;
const float URANUS_RADIUS = 0.3;
const float NEPTUNE_RADIUS = 0.3;
const float PLUTO_RADIUS = 0.05;
const float SUN_RADIUS = 1.0;
const float SKY_BOX_RADIUS = 15.0;

const float MERCURY_ORBIT_RADIUS = 1.5;
const float VENUS_ORBIT_RADIUS = 2.0;
const float MARS_ORBIT_RADIUS = 3.5;
const float JUPITER_ORBIT_RADIUS = 5.0;
const float SATURN_ORBIT_RADIUS = 7.0;
const float URANUS_ORBIT_RADIUS = 8.5;
const float NEPTUNE_ORBIT_RADIUS = 9.0;
const float PLUTO_ORBIT_RADIUS = 10.0;
const float EARTH_ORBIT_RADIUS = 3.0;
const float MOON_ORBIT_RADIUS = 0.50;

const float MERCURY_ORBIT_DUR = 88;
const float VENUS_ORBIT_DUR = 225;
const float EARTH_ORBIT_DUR = 365;
const float MARS_ORBIT_DUR = 686;
const float JUPITER_ORBIT_DUR = 4333;
const float SATURN_ORBIT_DUR = 10759;
const float URANUS_ORBIT_DUR = 30685;
const float NEPTUNE_ORBIT_DUR = 60190;
const float PLUTO_ORBIT_DUR = 90800;

const float MERCURY_ROTATION_DUR = 58.65;
const float VENUS_ROTATION_DUR = -243;
const float MARS_ROTATION_DUR= 	 	 1;
const float JUPITER_ROTATION_DUR=  0.4;
const float SATURN_ROTATION_DUR=   0.4;
const float URANUS_ROTATION_DUR=	 -0.7;
const float NEPTUNE_ROTATION_DUR=  0.7;
const float PLUTO_ROTATION_DUR= 	 -6;
const float EARTH_ROTATION_DUR    = 1.00;


const float MERCURY_INCLINATION = 7;
const float VENUS_INCLINATION   = 3.39f;
const float MARS_INCLINATION    = 1.85;
const float JUPITER_INCLINATION = 1.3;
const float SATURN_INCLINATION  = 2.49;
const float URANUS_INCLINATION  = 0.77;
const float NEPTUNE_INCLINATION = 1.77;
const float PLUTO_INCLINATION   = 17.2;
const float EARTH_INCLINATION   = 0;

#endif
