#include "Light.h"
#include <ctime>
#include <cstdlib>

float rando(){
    return float(rand())/RAND_MAX;
}
Light::Light(Vec3Df midpoint, float Radius, Vec3Df Normal, Vec3Df col,int numerofpoints){
	midPoint = midpoint;
	normal = Normal;
	normal.normalize();
	radius = Radius;
	material = Material();
	material.set_Ka(col[0],col[1],col[2]);
        colour = col/numerofpoints;
        light_num=numerofpoints;
}

Hit Light::intersect(Vec3Df origin, Vec3Df dest){
	float numerator = Vec3Df::dotProduct(midPoint-origin, normal);
	float denominator = Vec3Df::dotProduct(dest, normal);

	if(numerator == 0 && denominator == 0){
		return Hit(2, origin, normal, material);
	} else if(denominator == 0){
		return Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0), material);
	}

	float d = numerator/denominator;
	if(d < 0){
		return Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0), material);
	}
	Vec3Df hitpoint = origin+d*dest;

	if((hitpoint-midPoint).getLength() <= radius){
		return Hit(2, hitpoint, normal, material);
	} else {
		return Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0), material);
	}
}

std::vector<Vec3Df> Light::getPointLights(){

	std::vector<Vec3Df> pointLights;

	Vec3Df vec1 = Vec3Df::crossProduct(normal, Vec3Df(normal[0]+1, normal[1]-1, normal[2]+2));
	Vec3Df vec2 = Vec3Df::crossProduct(vec1, normal);
	vec1.normalize();
	vec1 *= radius;
	vec2.normalize();
	vec2 *= radius;

	//pointLights.push_back(midPoint);

	for(float i =0; i <= light_num; i++){
        	pointLights.push_back(rando()*vec1+rando()*vec2+midPoint);	
	}

	return pointLights;
}

