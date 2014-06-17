#ifndef RAYTRACING_Hjdslkjfadjfasljf
#define RAYTRACING_Hjdslkjfadjfasljf
#include <vector>
#include "mesh.h"
#include <ctime>
#include <cstdlib>
#include "sphere.h"
#include "initialize.h"

//a function to debug --- you can draw in OpenGL here
void yourDebugDraw();
//you can use this function to transform a click to an origin and destination
//the last two values will be changed. There is no need to define this function.
//it is defined elsewhere
void produceRay(int x_I, int y_I, Vec3Df & origin, Vec3Df & dest);

//your main function to rewrite
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest);
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest, int number);

//Hacked testing method
Hit gethits(const Vec3Df & origin, const Vec3Df & dest);

//want keyboard interaction? Here it is...
void yourKeyboardFunc(char t, int x, int y);

#endif