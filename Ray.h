#ifndef RAY_H
#define RAY_H

#include "Vec3D.h"
#include "hit.h"

enum RayType{
	SHADOW_RAY,
	PRIMARY_RAY,
	SECONDARY_RAY
};

class Ray{

	public:		
		Vec3Df origin;
		Vec3Df dest;
		Vec3Df colour;
		RayType type;
		Hit previous_hit;
		Vec3Df light;

		Ray(Vec3Df origin, Vec3Df dest, Vec3Df colour, RayType type, Hit previous_hit);
		Ray reflectionRay(Hit h);
		Ray refractionRay(Hit h, float medium1, float medium2);
		void pprint();
		void setLight(Vec3Df light);
};
#endif