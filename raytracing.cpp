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
#include "sphere.h"
#include "complexObject.h"
#include "shading.h"
#include "backward_shading.h"
#include "initialize.h"

//Contain colours within the range of 0-1
Vec3Df colourclamp(const Vec3Df & colour){
    Vec3Df clamped = colour;
    for(int i=0;i<3;i++){
        if(clamped[i]>1){
            clamped[i]=1;
        }
        if(clamped[i]<0){
            clamped[i]=0;
        }
    }
    return clamped;
}
Vec3Df colourNorm(const Vec3Df & colour){
        Vec3Df ret = colour;
    for(int i=0;i<3;i++){
            ret[i]=1-pow(0.3,colour[i]);
        }
}

Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest) {
  // int colournorm=1;
  Vec3Df colour= backward_shading_routine(scene, origin, dest);
  //if(colournorm){
     // return colourNorm(colour);
  // }
  return colour;
}

//return the color of your pixel.
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest,
		int maxNumberOfBounces) {
    	int numberOfRays = 1;
        Vec3Df dir = dest-origin;
        dir.normalize();
        Vec3Df rorigin = origin+dir*0.1;
	if (maxNumberOfBounces < 0) {
		return Vec3Df(0, 0, 0);
	}
	Hit hit = scene.intersect(rorigin, dest);
	if (hit.isHit != 0) {
		Vec3Df colour = findColour2(hit, rorigin, maxNumberOfBounces ,numberOfRays);
		return colour;
	} else {
		return Vec3Df(0, 0, 0);
	}
}

void yourDebugDraw() {
  //draw open gl debug stuff
  //this function is called every frame
  //as an example:
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glColor3f(0, 1, 1);
  glBegin(GL_LINES);
  glVertex3f(testRayOrigin[0], testRayOrigin[1], testRayOrigin[2]);
  glVertex3f(testRayDestination[0], testRayDestination[1], testRayDestination[2]);
  glEnd();
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex3fv(MyLightPositions[0].pointer());
  glEnd();
  glPopAttrib();
}

void yourKeyboardFunc(char key, int x, int y) {
  // do what you want with the keyboard input key.
  // x, y are the screen position

  switch (key)
    case 'd': {
      // Debug ray:

      // here I use it to get the coordinates of a ray, which I then draw in
      // the debug function.
      produceRay(x, y,                   testRayOrigin, testRayDestination);
      Vec3Df testRay = performRayTracing(testRayOrigin, testRayDestination);
      Hit hit =          scene.intersect(testRayOrigin, testRayDestination);
      std::cout << "Colour: " << testRay.toString() << std::endl;
      // if (hit.isHit) {
      //   std::cout << "Hit: " << hit.toString() << std::endl;
      // } else {
      //   std::cout << "Void" << std::endl;
      // }
    }
  std::cout << key << " pressed! The mouse was in location " << x << "," << y << "!"
  		<< std::endl;

}
