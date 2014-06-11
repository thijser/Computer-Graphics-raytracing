#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include "raytracing.h"
#include <ctime>
#include <cstdlib>

//temporary variables
Vec3Df testRayOrigin;
Vec3Df testRayDestination;
//use this function for any preprocessing of the mesh.

void init()
{//seed the random generator
	srand ( time(0) );
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


//return the color of your pixel.
Vec3Df performRayTracing(const Vec3Df & origin, const Vec3Df & dest)
{
//	int triangleIndex=0;
//	Vec3Df closesthit=0;
//	int closestIndex=0;
//	for(int i=0;i< sizeof(MyMesh.triangles);i++){
//		triangleIndex++;

		//Vec3Df hitpos=CollisionTriangleTest(MyMesh.triangles[i],dest,origin);
//		if(hitpos!=NULLvec3Df){
		//	closesthit=closest(origin,closesthit,hitpos);
		//	closestIndex=triangleIndex;
//		}
//	}


	return Vec3Df(1,0,0);
}

Vec3Df closest(const Vec3Df & origin,const Vec3Df & v1,const Vec3Df & v2){

}
Vec3Df findColour (const Vec3Df & position,const Vec3Df & normal,Material & mat,Vec3Df & camera  ){

	Vec3Df diffuse = mat.Kd();
	Vec3Df ambient = mat.Ka();
	Vec3Df specular = mat.Ks();
	float shininess = mat.Ns();
	Vec3Df ambientres=ambient;

	Vec3Df diffuseres= diffuse*performRayTracing(position,Vec3Df(0,0,0));
	float transparancy=mat.Tr();

	return ambient;

}

Vec3Df RandomVector(){
	int r1 = rand()%100000-50000;
	int r2 = rand()%100000-50000;
	int r3 = rand()%100000-50000;
	float f1=(((float)(r1))/50000);
	float f2=(((float)(r1))/50000);
	float f3=(((float)(r1))/50000);
	return Vec3Df(f1,f2,f3);

}
Vec3Df GaussianVector(){

}
/**
 * tests for collision, if collision occurs return the position else return 0 (null).
 */
Vec3Df CollisionTriangleTest(Triangle T,const Vec3Df & rayDirection, const Vec3Df & rayOrigin){

	return 0;
}
/*
 * tests for collision, if collision occurs return the position else return 0 (null).
 */
Vec3Df CollisionCircleTest(const Vec3Df & v1,const Vec3Df & radius,Vec3Df & rayDirection, const Vec3Df & rayOrigin){

	return 0;
}
void yourDebugDraw()
{
	//draw open gl debug stuff
	//this function is called every frame

	//as an example:
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glColor3f(0,1,1);
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

void yourKeyboardFunc(char t, int x, int y)
{
	// do what you want with the keyboard input t.
	// x, y are the screen position

	//here I use it to get the coordinates of a ray, which I then draw in the debug function.
	produceRay(x, y, testRayOrigin, testRayDestination);

	std::cout<<t<<" pressed! The mouse was in location "<<x<<","<<y<<"!"<<std::endl;

}
