#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "hit.h"

class Intersectable
{
	public:
		virtual Hit intersect(Vec3Df origin, Vec3Df dest) = 0;
};

#endif