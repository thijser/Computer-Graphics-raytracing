#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include "raytracing.h"
#include <ctime>
#include <cstdlib>
#include "sphere.h"
#include "complexObject.h"
#include "shading.h"
#include "initialize.h"

Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest) {

	int numberOfRays = 1;
	int maxNumberOfBounces = 4;
	Vec3Df colour = Vec3Df(0, 0, 0);

	for (int i = 0; i < numberOfRays; i++) {
		colour = colour + performRayTracing(origin, dest, maxNumberOfBounces);
	}
	return colour / numberOfRays;
}

//return the color of your pixel.
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest,
		int maxNumberOfBounces) {
        Vec3Df dir = dest-origin; 
        dir.normalize();
        Vec3Df rorigin = origin+dir*0.1; 
	if (maxNumberOfBounces < 0) {
		return Vec3Df(0, 0, 0);
	}
	Hit hit = gethits(rorigin,dest);
	if (hit.isHit != 0) {
			Vec3Df colour = findColour(hit, rorigin, maxNumberOfBounces - 1);
			return colour;
		} else {
			return Vec3Df(0, 0, 0);
		}
}

/*
 * placeholder datastructure holding 2 spheres
 */
Hit gethits(const Vec3Df & origin, const Vec3Df & dest){
	Intersectable * s = new Sphere(Vec3Df(0, 0, 0), 2, testMat1);
	Hit h = s->intersect(origin, dest);

	Intersectable * s2 = new Sphere(Vec3Df(-2, 0, 0), 2, testMat2);
	Hit h2 = s2->intersect(origin, dest);
	if (h.isHit!=0)
		return h;
	else
		return h2;
 	
	//Let op: Langzaam!
	Triangle t;
	ComplexObject co = ComplexObject(t, testMat3, MyMesh);

	for(int i = 0; i < MyMesh.triangles.size(); i++) {
		// std::cout<<"Now on iteration: "<<i<<std::endl;
	  t = MyMesh.triangles[i];
	  co = ComplexObject(t, testMat3, MyMesh);

	  if(co.intersect(origin, dest).isHit != 0){
		return co.intersect(origin, dest);
	  }
	}
	return co.intersect(origin, dest);
	
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

void yourKeyboardFunc(char t, int x, int y) {
// do what you want with the keyboard input t.
// x, y are the screen position

//here I use it to get the coordinates of a ray, which I then draw in the debug function.
produceRay(x, y, testRayOrigin, testRayDestination);

std::cout << t << " pressed! The mouse was in location " << x << "," << y << "!"
		<< std::endl;

}
