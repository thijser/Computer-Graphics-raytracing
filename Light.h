#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3D.h"
#include "hit.h"

class Light{

	public:
        Vec3Df midPoint;
	Vec3Df normal;
	float radius;
	Material material;
        Vec3Df colour; 
		Light(Vec3Df midPoint, float radius, Vec3Df normal,Vec3Df col);		
		Hit intersect(Vec3Df origin, Vec3Df dest);
		std::vector<Vec3Df> getPointLights();
};

#endif
