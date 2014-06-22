#ifndef INITIALIZE_H
#define INITIALIZE_H
#include <vector>
#include "mesh.h"
#include <ctime>
#include <cstdlib>
#include "Scene.h"
#include "Light.h"
#include "ppm.h"


extern Scene scene;

extern Vec3Df testRayOrigin;
extern Vec3Df testRayDestination;
extern Material testMat1;
extern Material testMat2;
extern Material testMat3;
extern std::vector<Vec3Df> LightsPositions;
extern std::vector<Vec3Df> LightsColours;
extern std::vector<Light> Lights; 

extern Mesh MyMesh; //Main mesh
extern std::vector<Vec3Df> MyLightPositions;
extern Vec3Df MyCameraPosition; //currCamera
extern unsigned int WindowSize_X;//window resolution width
extern unsigned int WindowSize_Y;//window resolution height
extern unsigned int RayTracingResolutionX;  // largeur fenetre
extern unsigned int RayTracingResolutionY;  // largeur fenetre


//use this function for any preprocessing of the mesh.
void init();

#endif
