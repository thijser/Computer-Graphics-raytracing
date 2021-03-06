#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h> // This is located in the “GLUT” directory on MacOSX
#endif
#include <cstdlib>
#include "utility_methods.h"
#include "shading.h"
#include "raytracing.h"
/**
 * ensures that a colour does not go above 1 or bellow 0.
 */

//Method diffuseColour returns diffuse colour FACTOR at a position
float diffusefac(const Vec3Df & vertexPos, Vec3Df & normal,
		const Vec3Df & lightPos) {
	Vec3Df nvertexPos = vertexPos;
	Vec3Df nlightPos = lightPos-vertexPos;
	Vec3Df nnormal = normal;
	nlightPos.normalize();
	nnormal.normalize();


	float shade = Vec3Df::dotProduct(nlightPos, normal);
	if (shade<0){
		shade=0;
	}
	return shade;
}

//Method blingPhongSpeculair returns the blinn phong shading FACTOR at a specific point.
float blinnPhongSpecularfac(const Vec3Df & vertexPos, Vec3Df & normal,
		const Vec3Df & lightPos, const Vec3Df & cameraPos,float shininess) {
	Vec3Df relativeLightPos = (lightPos - vertexPos);
	relativeLightPos.normalize();
	Vec3Df relativeCameraPos = (cameraPos - vertexPos);
	relativeCameraPos.normalize();

	Vec3Df halfway = (relativeLightPos + relativeCameraPos);
	halfway.normalize();

	float blingnphongyness = Vec3Df::dotProduct(normal, halfway);
	if (blingnphongyness < 0) {
		blingnphongyness = 0;
	}
	float light = powf(blingnphongyness, shininess);
	return light;
}

//Main function being called. Returns a colour at position using all other methods (Ambient, Speculair and Diffuse)
//Takes speculair and diffuse factor and combines them with Ks and Kd
Vec3Df findColour2(Hit h, const Vec3Df & camera, int number,int rays){
    	Vec3Df ambient = h.material.Ka();
        double totalfact=1;
        Vec3Df totalColour=Vec3Df(0,0,0);
        for(int i=0;i<rays;i++){
			Vec3Df random = GaussianVector();
		if (0 > h.normal.dotProduct(h.normal, random)) {
			random = random * -1;
		}
		double diff = diffusefac(h.hitPoint,h.normal,random+h.hitPoint);
		double specf = blinnPhongSpecularfac(h.hitPoint,h.normal,random+h.hitPoint,camera,h.material.Ns());

		Vec3Df colour = performRayTracing(h.hitPoint, random+h.hitPoint, number - 1);

		totalColour += (diff*h.material.Kd()*colour) + (colour*specf*h.material.Ks());

		totalfact += diff + specf;
        }
	return totalColour / totalfact + ambient;
}
