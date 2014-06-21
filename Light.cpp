#include "Light.h"


Light::Light(Vec3Df midpoint, float Radius, Vec3Df Normal){
	midPoint = midpoint;
	normal = Normal;
	normal.normalize();
	radius = Radius;
	material = Material();
	material.set_Ka(0.5,0.5,0.5);
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
	Vec3Df hitpoint = origin+d*dest;

	if((hitpoint-midPoint).getLength() <= radius){
		return Hit(2, hitpoint, normal, material);
	} else {
		return Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0), material);
	}
}

std::vector<Vec3Df> Light::getPointLights(){
	int light_num = 1;

	std::vector<Vec3Df> pointLights;

	Vec3Df vec1 = Vec3Df::crossProduct(normal, Vec3Df(normal[0]+1, normal[1]-1, normal[2]+2));
	Vec3Df vec2 = Vec3Df::crossProduct(vec1, normal);
	vec1.normalize();
	vec1 *= radius;
	vec2.normalize();
	vec2 *= radius;

	//pointLights.push_back(midPoint);

	for(float i = (1/light_num); i <= 1; i+=(1/light_num)){
		for(float j = (1/light_num); j <= 1; j+=(1/light_num)){
	 		pointLights.push_back(midPoint);
	 	}	
	}

	return pointLights;
}

