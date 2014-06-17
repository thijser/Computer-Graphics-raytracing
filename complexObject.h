#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include "intersectable.h"

class ComplexObject: public Intersectable
{
	Triangle T;
	Material material;
	Mesh myMesh;

	public:
		ComplexObject(Triangle coT, Material material, Mesh comyMesh);
		Hit intersect(Vec3Df origin, Vec3Df dest);
};

#endif
