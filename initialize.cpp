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
#include "TexturedSphere.h"

//temporary variables
Vec3Df testRayOrigin;
Vec3Df testRayDestination;
Material testMat1;
Material testMat2;
Material testMat3;
Material testMat4;
std::vector<Vec3Df> LightsPositions;
std::vector<Vec3Df> LightsColours;
std::vector<Light> Lights;
Scene scene;
Config config;
Mesh Oven;
//ple this function for any preprocessing of the mesh.

void init() { //seed the random generator
  srand(time(0));
  Config configUltra =          Config("Ultra", 1680 , 2460 ,1680 , 2460 ,16 ,16);
  Config configHigh =     Config("1080 HD", 1080, 1920, 1080, 1920, 4, 4);
  Config configStandard = Config("Standard", 800,  800,  800,  800,  3, 4);
  Config configMedium = Config("Medium", 800, 800, 800, 800, 2, 2);
  Config configLow =      Config("Low",      200,  200,  800,  800,  1, 1);
  config = configLow;
  // LightsPositions.assign(1,Vec3Df(0,-1,-1));
  // LightsColours.assign(1,Vec3Df(1,1,1));
  // LightsPositions.assign(2,Vec3Df(-12,0,-1));
  // LightsColours.assign(2,Vec3Df(1,1,1));
  // LightsPositions.assign(3,Vec3Df(0,14,16));
  // LightsColours.assign(3,Vec3Df(1,1,1));
  // LightsPositions.assign(4,Vec3Df(0,100,1));
  // LightsColours.assign(4,Vec3Df(1,1,1));
  // LightsPositions.assign(5,Vec3Df(0,0,0));
  // LightsColours.assign(5,Vec3Df(1,1,1));

  PPM image = PPM("map.ppm");

  //cout << image.getWidth() << " " << image.getHeight() << "\n" << image.image.size() << " " << image.image[0].size() << "\n";
  //cout << image.getWidth() << "\n";
  //cout << image.getHeight() << "\n";

  testMat1 = Material();
  testMat1.set_Kd(1, 0, 0);
  testMat1.set_Ka(1, 0.005, 0.005);
  testMat1.set_Ks(1, 1, 1);
  testMat1.set_Ns(100);

  testMat2 = Material();
  testMat2.set_Kd(0.1, 0.1, 0.4);
  testMat2.set_Ka(0.1,0.1,0.1);
  testMat2.set_Ks(0.3, 0.2, 0.5);
  testMat2.set_Ns(100);
  testMat2.set_Tr(0.5);

  testMat3 = Material();
  testMat3.set_Kd(0, 1, 1);
  testMat3.set_Ka(0, 0, 0);
  testMat3.set_Ks(1, 1, 1);
  testMat3.set_Ns(100);

  testMat4 = Material();
  testMat4.set_Kd(0,0,0);
  testMat4.set_Ka(0,0,0);
  testMat4.set_Ks(1,1,1);
  testMat4.set_Ns(100);

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
  objs.push_back(new ComplexObject(MyMesh, testMat2));
  LightsPositions.push_back(Vec3Df(0,2,1));
  Lights.push_back( Light( Vec3Df(0,1.5,1.3), 0.5, Vec3Df(0,-1,0),Vec3Df(1,1,1), 20 ) );
  Lights.push_back( Light( Vec3Df(1,0,1.3), 0.5, Vec3Df(-1,0,0),Vec3Df(1,1,1),20 ));
  //objs.push_back(new Sphere(Vec3Df(0, -0.5, 1), 0.5, testMat2));
  objs.push_back(new TexturedSphere(Vec3Df(0, -0.5, 1), 0.5, testMat4, "map.ppm"));
 //objs.push_back(new Sphere(Vec3Df(0, 0.2, 1.3), 0.1, testMat1));
  //objs.push_back(new Sphere(Vec3Df(-4, 0, 0), 4.5, testMat3));
  //objs.push_back(new Sphere(Vec3Df(4, 0, 1), 4, testMat3));
  //objs.push_back(new Sphere(Vec3Df(0, 0, 1.5), 0.1, testMat3));
 
  
  Oven.loadMesh("oven.obj", true);
  Oven.computeVertexNormals();
  objs.push_back(new ComplexObject(Oven, testMat1));//Oven.materials.back()));


   scene = Scene(objs, Lights);
   
   
}


