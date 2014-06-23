#ifndef HIT_H
#define HIT_H

#include <string>
#include "Vec3D.h"
#include "mesh.h"

class Hit
{
	public:
		int isHit;
		Vec3Df hitPoint;
		Vec3Df normal;
		Material material;
    inline Hit(void) {
      isHit = 0;
      hitPoint = Vec3Df(0,0,0);
      normal = hitPoint;
      material = Material();
    }

		Hit(int fisHit, Vec3Df fhitPoint, Vec3Df fnormal, Material fmaterial){
			isHit = fisHit;
			hitPoint = fhitPoint;
			normal = fnormal;
			material = fmaterial;
		}

    inline std::string toString() {
        std::string hit;
        if (isHit)
          hit = "HIT";
        else
          hit = "no-hit";

        hit = "Hit(" + hit + ", hitPoint:" + hitPoint.toString();
        hit += ", normal: " + normal.toString();
        hit += ", material:" + material.name() + ")";
    }
};

#endif
