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
#include "camera.h"
#include "utils.h"


	void Camera::moveX(float d) {
		// if(!(isBeyond(SKY_BOX_RADIUS))){
			Vector3f right = up.cross(center - eye).unit();
			eye = eye + right * d;
			center = center + right * d;
		// }
	}

	void Camera::moveY(float d) {
		// if(!(isBeyond(SKY_BOX_RADIUS))){
			eye = eye + up.unit() * d;
			center = center + up.unit() * d;
		// }
	}

	void Camera::moveZ(float d) {
		// if(!(isBeyond(SKY_BOX_RADIUS))){
			Vector3f view = (center - eye).unit();
			eye = eye + view * d;
			center = center + view * d;
		// }
	}

	void Camera::rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void Camera::rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void Camera::look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}

	bool Camera::isBeyond(float a){
		return (abs(eye.x - a) <= 0) || (abs(eye.y - a) <= 0) || (abs(eye.z - a) <= 0);
	}