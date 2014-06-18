#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h> // This is located in the “GLUT” directory on MacOSX
#endif
#include "raytracing.h"
#include <ctime>
#include <cstdlib>
#include "initialize.h"
#include "Scene.h"
#include "complexObject.h"
//temporary variables
Vec3Df testRayOrigin;
Vec3Df testRayDestination;
Material testMat1;
Material testMat2;
Material testMat3;
std::vector<Vec3Df> LightsPositions;
std::vector<Vec3Df> LightsColours;
Scene scene;

//use this function for any preprocessing of the mesh.

void init() { //seed the random generator
	srand(time(0));
	LightsPositions.assign(1,Vec3Df(0,-1,-1));
	LightsColours.assign(1,Vec3Df(1,1,1));
	LightsPositions.assign(2,Vec3Df(-12,0,-1));
	LightsColours.assign(2,Vec3Df(1,1,1));
	LightsPositions.assign(3,Vec3Df(0,14,16));
	LightsColours.assign(3,Vec3Df(1,1,1));
	LightsPositions.assign(4,Vec3Df(0,100,1));
	LightsColours.assign(4,Vec3Df(1,1,1));
	LightsPositions.assign(5,Vec3Df(0,0,0));
	LightsColours.assign(5,Vec3Df(1,1,1));

	testMat1 = Material();
	testMat1.set_Kd(0, 0, 0);
	testMat1.set_Ka(1, 1, 0);
	testMat1.set_Ks(0.2, 0.5, 0.1);
	testMat1.set_Ns(5);

	testMat2 = Material();
	testMat2.set_Kd(0, 1, 0);
	testMat2.set_Ka(0.0, 0, 0.0);
	testMat2.set_Ks(1, 0, 1);
	testMat2.set_Ns(5);

	testMat3 = Material();
	testMat3.set_Kd(1, 0, 0);
	testMat3.set_Ka(1, 0, 0);
	testMat3.set_Ks(1, 1, 1);
	testMat3.set_Ns(5);

	//load the mesh file
	//feel free to replace cube by a path to another model
	//please realize that not all OBJ files will successfully load.
	//Nonetheless, if they come from Blender, they should.
	MyMesh.loadMesh("cube.obj", true);
	//MyMesh.loadMesh("dodgeColorTest.obj", true);
	MyMesh.computeVertexNormals();

	//one first move: initialize the first light source
	//at least ONE light source has to be in the scene!!!
	//here, we set it to the current location of the camera
	MyLightPositions.push_back(MyCameraPosition);

	//Create scene
	std::vector<Intersectable*> objs;
	// objs.push_back(new ComplexObject(testMat1,MyMesh));
  	objs.push_back(new Sphere(Vec3Df(1, 0, -3), 2, testMat1));
  	objs.push_back(new Sphere(Vec3Df(1, 3, -3), 2, testMat2));
	scene = Scene(objs);
}


