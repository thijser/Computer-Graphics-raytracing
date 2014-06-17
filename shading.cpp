#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <cstdlib>
#include "utility_methods.h"
#include "shading.h"
#include "raytracing.h"


//Method blingPhongSpeculair returns the blinn phong shading at a specific point.
Vec3Df blingPhongSpeculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view, const Vec3Df & Lightposition,const Vec3Df & LightColour){

	Vec3Df relativeLightPos = (Lightposition - position);
	relativeLightPos.normalize();
	Vec3Df relativeCameraPos = (view - position);
	relativeCameraPos.normalize();

	Vec3Df halfway = (relativeLightPos + relativeCameraPos)
			/ (relativeLightPos + relativeCameraPos).getLength();
	halfway.normalize();

	float blingnphongyness = Vec3Df::dotProduct(normal, halfway);
	if (blingnphongyness < 0) {
		blingnphongyness = 0;
	}
	float shininess = mat.Ns();
	float light = powf(blingnphongyness, shininess);

	return light * mat.Ks()*LightColour;
}

//Method speculair returns speculair (including shade and slight reflection of surroundings)
Vec3Df speculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view, int number) {
	Vec3Df reflectiveRay = getReflectionVector(normal, view, position);
	Vec3Df specRay = reflectiveRay + GaussianVector() / mat.Ns();
	Vec3Df speculairres = mat.Ks()
			* performRayTracing(position, specRay+position, number - 1);
	return speculairres;

}

//Method diffuseColour returns diffuse colour at a position
Vec3Df diffuseColour(Material & mat, const Vec3Df & position,
		const Vec3Df & normal, int number) {
	Vec3Df random = RandomVector();
	if (0 > normal.dotProduct(normal, random)) {
		random = random * -1;
	}

	return mat.Kd() * performRayTracing(position, random+position, number - 1);
}

//Method lightbasedSpeculair returns colour at position includes blinn phong
Vec3Df lightbasedSpeculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view){
		Vec3Df colour=  Vec3Df(0,0,0);
		for(int i =0;i<LightsPositions.size();i++){

			Hit trace = gethits(position,LightsPositions[i]);
			if(trace.isHit==0){
				colour=colour+blingPhongSpeculair(mat,position,normal,view,LightsPositions[i],LightsColours[i]);
			}else if((position.distance(position,LightsPositions[i])<=position.distance(position,trace.hitPoint))) {
				colour=colour+blingPhongSpeculair(mat,position,normal,view,LightsPositions[i],LightsColours[i]);
			}
		}

		return colour;
}

//Method find colour returns color for a given hit.
Vec3Df findColour(Hit h, const Vec3Df & camera, int number) {
	Vec3Df colour = h.material.Ka();
	colour = colour + diffuseColour(h.material, h.hitPoint, h.normal, number);
	colour = colour
			+Speculair(h.material, h.hitPoint, h.normal, camera,number);
	h.hitPoint.normalize();
	return colour;
}


