#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <cstdlib>
#include "utility_methods.h"
#include "shading.h"
#include "raytracing.h"
/**
 * ensures that a colour does not go above 1 or bellow 0. 
 */

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

Vec3Df findColour2(Hit h, const Vec3Df & camera, int number,int rays){
    	Vec3Df ambient = h.material.Ka();
        double totalfact=1;
        Vec3Df totalColour=Vec3Df(0,0,0);
        for(int i=0;i<rays;i++){
			Vec3Df random = RandomVector();
		if (0 > h.normal.dotProduct(h.normal, random)) {
			random = random * -1;
		}
		double diff = diffusefac(h.hitPoint,h.normal,random+h.hitPoint);
		double specf = blinnPhongSpecularfac(h.hitPoint,h.normal,random+h.hitPoint,camera,h.material.Ns());
		
		Vec3Df colour = performRayTracing(h.hitPoint, random+h.hitPoint, number - 1);   
		
		totalColour = totalColour+(diff*h.material.Kd()*colour)+(colour*specf*h.material.Ks());
		
		totalfact = totalfact+diff+specf;
		 
        }
        return totalColour/totalfact+ambient;
}
