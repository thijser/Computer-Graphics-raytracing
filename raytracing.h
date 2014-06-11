#ifndef RAYTRACING_Hjdslkjfadjfasljf
#define RAYTRACING_Hjdslkjfadjfasljf
#include <vector>
#include "mesh.h"
#include <ctime>
#include <cstdlib>
//Welcome to your assignment...
//this is an important file, raytracing.cpp is what you need to fill out

extern Mesh MyMesh; //Main mesh
extern std::vector<Vec3Df> MyLightPositions;
extern Vec3Df MyCameraPosition; //currCamera
extern unsigned int WindowSize_X;//window resolution width
extern unsigned int WindowSize_Y;//window resolution height
extern unsigned int RayTracingResolutionX;  // largeur fenetre
extern unsigned int RayTracingResolutionY;  // largeur fenetre


//use this function for any preprocessing of the mesh.
void init();
//a function to debug --- you can draw in OpenGL here
void yourDebugDraw();
//you can use this function to transform a click to an origin and destination
//the last two values will be changed. There is no need to define this function.
//it is defined elsewhere
void produceRay(int x_I, int y_I, Vec3Df & origin, Vec3Df & dest);
Vec3Df findColour (const Vec3Df & position,const Vec3Df & normal,Vec3Df & camera);
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest,int number);
float generateGaussianNoise(const float & variance);
Vec3Df closest(const Vec3Df & origin,const Vec3Df & v1,const Vec3Df & v2);
Vec3Df CollisionTriangleTest(Triangle T,const Vec3Df & rayDirection, const Vec3Df & rayOrigin);
Vec3Df CollisionCircleTest(const Vec3Df & v1,const Vec3Df & radius,Vec3Df & rayDirection, const Vec3Df & rayOrigin);
//your main function to rewrite
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest);
Vec3Df RandomVector();
Vec3Df GaussianVector();
Vec3Df getReflectionVector(const Vec3Df & normal, const Vec3Df & cameraPos, const Vec3Df & vertexPos);
//want keyboard interaction? Here it is...
void yourKeyboardFunc(char t, int x, int y);

#endif
