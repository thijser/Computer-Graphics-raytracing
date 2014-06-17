#ifndef HIT_H
#define HIT_H

#include "Vec3D.h"
#include "mesh.h"

class Hit
{
	public:
		int isHit;
		Vec3Df hitPoint;
		Vec3Df normal;
		Material material;

		Hit(int fisHit, Vec3Df fhitPoint, Vec3Df fnormal, Material fmaterial){
			isHit = fisHit;
			hitPoint = fhitPoint;
			normal = fnormal;
			material = fmaterial;
		}
};

#endif