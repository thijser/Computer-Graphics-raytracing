#ifndef SPHERE_H
#define SPHERE_H

#include "intersectable.h"

class Sphere: public Intersectable
{
	Vec3Df sphereMidPoint;
	float sphereRadius;
	Material material;

	public:
		Sphere(Vec3Df midPoint, float radius, Material material);
		Hit intersect(Vec3Df origin, Vec3Df dest);
};

#endif