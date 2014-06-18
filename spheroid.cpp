#include "spheroid.h"

void Spheroid::init(Vec3Df midPoint, Vec3Df radii, Material mat){
	spheroidMidPoint = midPoint;
	radii = radii;
	material = mat;
}

Spheroid::Spheroid(Vec3Df midPoint, float radiusX, float radiusY, float radiusZ, Material mat){
	init(midPoint, Vec3Df(radiusX,radiusY,radiusZ), mat);
}
Spheroid::Spheroid(Vec3Df midPoint, Vec3Df radii, Material mat){
	init(midPoint, radii, mat);
}

Vec3Df Spheroid::getNormal(Vec3Df hitPoint) {
	Vec3Df normal = Vec3Df(hitPoint[0]/pow(radii[0],2),hitPoint[1]/pow(radii[1],2),hitPoint[2]/pow(radii[2],2));
	normal.normalize();
	return normal;	
}

Hit Spheroid::intersect(Vec3Df origin, Vec3Df dest){
	Vec3Df o = origin - spheroidMidPoint;
	Vec3Df d = dest - spheroidMidPoint;

	float A = pow(d[0]/radii[0],2) + pow(d[1]/radii[1],2) + pow(d[2]/radii[2],2);
	float B = 2*(d[0]*o[0]/pow(radii[0],2) + d[1]*o[1]/pow(radii[1],2) + d[2]*o[2]/pow(radii[2],2));
	float C = pow(o[0]/radii[0],2) + pow(o[1]/radii[1],2) + pow(o[2]/radii[2],2) - 1;

	float discriminant = B*B-4*A*C;

	if(discriminant < 0){
		return Hit(0,Vec3Df(0,0,0), Vec3Df(0,0,0), material);
	} if(discriminant == 0){
		float t = (-1*B)/(2*A);
		Vec3Df hitpoint = (o+(d*t));
		return Hit(1, hitpoint+spheroidMidPoint, getNormal(hitpoint), material);
	} else{
		float t;
		float t1 = ((-1*B)-sqrt(discriminant))/(2*A);
		float t2 = ((-1*B)+sqrt(discriminant))/(2*A);

		if(t1 < 0){
			t = t2;
		} else if(t2 < 0){
			t = t1;
		} else if(t1 < t2){
			t = t1;
		} else {
			t = t2;
		}

		Vec3Df hitpoint = (o+(d*t));
		Vec3Df normal = getNormal(hitpoint);

		return Hit(1, hitpoint+spheroidMidPoint, getNormal(hitpoint), material);
	}
}
