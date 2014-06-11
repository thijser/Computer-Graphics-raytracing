#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include "raytracing.h"
#include <ctime>
#include <cstdlib>

#define TWO_PI 6.2831853071795864769252866

//temporary variables
Vec3Df testRayOrigin;
Vec3Df testRayDestination;
Material testMat1;
Material testMat2;
//use this function for any preprocessing of the mesh.

void init() { //seed the random generator
	srand(time(0));

	testMat1 = Material();
	testMat1.set_Kd(0, 0, 0);
	testMat1.set_Ka(0.1, 0, 0.5);
	testMat1.set_Ks(0, 0, 0);
	testMat1.set_Ns(11);

	testMat2 = Material();
	testMat2.set_Kd(0.5, 0.5, 0.5);
	testMat2.set_Ka(0.0, 0.5, 0.0);
	testMat2.set_Ks(0.5, 0.5, 0.5);
	testMat2.set_Ns(11);

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
}

Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest) {

	int numberOfRays = 10;
	int maxNumberOfBounces = 4;
	Vec3Df colour = Vec3Df(0, 0, 0);

	for (int i = 0; i < numberOfRays; i++) {
		colour = colour + performRayTracing(origin, dest, maxNumberOfBounces);
	}
	return colour / numberOfRays;
}

//return the color of your pixel.
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest,
		int number) {
	if (number < 0) {
		return Vec3Df(0, 0, 0);
	}
	Sphere s = Sphere(Vec3Df(2, 1, 1), 2, testMat1);
	Hit h = s.intersect(origin, dest);

	Sphere s2 = Sphere(Vec3Df(-2, 0, 0), 2, testMat2);
	Hit h2 = s2.intersect(origin, dest);

	if (h.isHit == 0) {
		if (h2.isHit) {
			Vec3Df colour = findColour(h2, origin, number - 1);
			return colour;
		} else {
			return Vec3Df(0, 0, 0);
		}
	} else {
		Vec3Df colour = findColour(h, origin, number - 1);
		return colour;

	}

}

Vec3Df closest(const Vec3Df & origin, const Vec3Df & v1, const Vec3Df & v2) {

}

Vec3Df ambientcolour(Material mat) {
	return mat.Ka();
}

Vec3Df diffusecolour(Material & mat, const Vec3Df & position,
		const Vec3Df & normal, int number) {
	Vec3Df random = RandomVector();
	if (0 > normal.dotProduct(normal, random)) {
		random = random * -1;
	}

	return mat.Kd() * performRayTracing(position, random+position, number - 1);
}

Vec3Df speculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view, int number) {
	Vec3Df reflectiveRay = getReflectionVector(normal, view, position);
	Vec3Df specRay = reflectiveRay + GaussianVector() / mat.Ns();
	Vec3Df speculairres = mat.Ks()
			* performRayTracing(position, specRay+position, number - 1);



}
Vec3Df findColour(Hit h, const Vec3Df & camera, int number) {
	Vec3Df colour = Vec3Df(0, 0, 0);
	colour = colour + ambientcolour(h.material);
	colour = colour + diffusecolour(h.material, h.hitPoint, h.normal, number);
	colour = colour
			+ speculair(h.material, h.hitPoint, h.normal, camera, number);
	return colour;
}


Vec3Df getRefractiveRay(const Vec3Df & normal, const Vec3Df & Camera,
	const Vec3Df & position) {
	return normal;
}

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
return Vec3Df(generateGaussianNoise(1), generateGaussianNoise(1),
		generateGaussianNoise(1));
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
Vec3Df getReflectionVector(const Vec3Df & normal, const Vec3Df & cameraPos,
	const Vec3Df & vertexPos) {
Vec3Df view = cameraPos - vertexPos;
Vec3Df norm = normal;
view.normalize();
norm.normalize();

float innerDotProduct = Vec3Df::dotProduct(view, norm);
return norm * (2 * innerDotProduct) - view;
}

/**
 * tests for collision, if collision occurs return the position else return 0 (null).
 */
Vec3Df CollisionTriangleTest(Triangle T, const Vec3Df & rayDirection,
	const Vec3Df & rayOrigin) {

return 0;
}
/*
 * tests for collision, if collision occurs return the position else return 0 (null).
 */
Vec3Df CollisionCircleTest(const Vec3Df & v1, const Vec3Df & radius,
	Vec3Df & rayDirection, const Vec3Df & rayOrigin) {

return 0;
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
