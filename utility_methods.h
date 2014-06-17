#ifndef UTILITY_METHODS_H
#define UTILITY_METHODS_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Vec3D.h"
#include "mesh.h"
#include "hit.h"

//Return Vector with random entries
Vec3Df RandomVector();

//Generate random Gaussian vector
	Vec3Df GaussianVector() ;

//Generates random gaussian numbers
//Based on http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
float generateGaussianNoise(const float &variance) ;


//Returns reflection vector for a given point on mesh from a certain starting point
Vec3Df getReflectionVector(const Vec3Df & normal, const Vec3Df & cameraPos, const Vec3Df & vertexPos);

#endif
