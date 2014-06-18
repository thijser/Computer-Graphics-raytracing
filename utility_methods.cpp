#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include "utility_methods.h"


#define TWO_PI 6.2831853071795864769252866

//Returns vector with random entries
Vec3Df RandomVector() {
	int r1 = rand() % 100000 - 50000;
	int r2 = rand() % 100000 - 50000;
	int r3 = rand() % 100000 - 50000;
	float f1 = (((float) (r1)) / 50000);
	float f2 = (((float) (r1)) / 50000);
	float f3 = (((float) (r1)) / 50000);
	return Vec3Df(f1, f2, f3);
}

//Generate random Gaussian vector
	Vec3Df GaussianVector() {
	return Vec3Df(generateGaussianNoise(1), generateGaussianNoise(1), generateGaussianNoise(1));
}

//Generates random gaussian numbers
//Based on http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
float generateGaussianNoise(const float &variance) {
	static bool hasSpare = false;
	static float rand1, rand2;

	if (hasSpare) {
		hasSpare = false;
		return sqrt(variance * rand1) * sin(rand2);
	}

	hasSpare = true;

	rand1 = rand() / ((float) RAND_MAX);
	if (rand1 < 1e-100)
		rand1 = 1e-100;
	rand1 = -2 * log(rand1);
	rand2 = (rand() / ((float) RAND_MAX)) * TWO_PI;

	return sqrt(variance * rand1) * cos(rand2);
}

//Returns reflection vector for a given point on mesh from a certain starting point
Vec3Df getReflectionVector(const Vec3Df & normal, const Vec3Df & cameraPos, const Vec3Df & vertexPos) {
	Vec3Df view = cameraPos - vertexPos;
	Vec3Df norm = normal;
	view.normalize();
	norm.normalize();

	float innerDotProduct = Vec3Df::dotProduct(view, norm);
	return norm * (2 * innerDotProduct) - view;
}


