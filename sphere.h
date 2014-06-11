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

class Sphere
{
	Vec3Df sphereMidPoint;
	float sphereRadius;
	Material mat;

	public:
		Sphere(Vec3Df midPoint, float radius){
			sphereMidPoint = midPoint;
			sphereRadius = radius;

			mat = Material();
			mat.set_Kd(1,0,0);
			mat.set_Ka(1,0,0);
			mat.set_Ks(1,0,0);
		}

		Hit intersect(Vec3Df origin, Vec3Df dest){
				Vec3Df o = origin - sphereMidPoint;
				Vec3Df d = dest - sphereMidPoint;

				float A = d[0]*d[0]+d[1]*d[1]+d[2]*d[2];
				float B = 2*(d[0]*o[0] + d[1]*o[1] + d[2]*o[2]);
				float C = o[0]*o[0]+o[1]*o[1]+o[2]*o[2]-sphereRadius*sphereRadius;

				float discriminant = B*B-4*A*C;

				if(discriminant < 0){
					return Hit(0,Vec3Df(0,0,0), Vec3Df(0,0,0), mat);
				} if(discriminant == 0){
					float t = (-1*B)/(2*A);
					Vec3Df hitpoint = (o+(d*t));
					Vec3Df normal = hitpoint;
					normal.normalize();
					return Hit(1, hitpoint+sphereMidPoint, normal, mat);
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
					Vec3Df normal = hitpoint;
					normal.normalize();

					return Hit(1, hitpoint+sphereMidPoint, normal, mat);
				}
		}
};