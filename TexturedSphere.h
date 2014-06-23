#ifndef TEXTURED_SPHERE_H
#define TEXTURED_SPHERE_H

#include "intersectable.h"
#include <string>
#include <math.h>
#include "ppm.h"


class TexturedSphere: public Intersectable
{
	Vec3Df sphereMidPoint;
	float sphereRadius;
	Material material;
	PPM image;

	public:
		TexturedSphere(Vec3Df midPoint, float radius, Material mat, std::string filename);
		Hit intersect(Vec3Df origin, Vec3Df dest);
};

#endif