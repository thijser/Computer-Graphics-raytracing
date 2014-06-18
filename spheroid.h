#ifndef SPHEROID_H
#define SPHEROID_H

#include "intersectable.h"

class Spheroid: public Intersectable
{
	Vec3Df spheroidMidPoint;
	Vec3Df radii;
	Material material;

	public:
		Spheroid(Vec3Df midPoint, Vec3Df radius, Material material);
		Spheroid(Vec3Df midPoint, float radiusX, float radiusY, float radiusZ, Material material);
		void init(Vec3Df midPoint, Vec3Df radius, Material material);
		Hit intersect(Vec3Df origin, Vec3Df dest);
	private:
		Vec3Df getNormal(Vec3Df hitPoint);
};

#endif
