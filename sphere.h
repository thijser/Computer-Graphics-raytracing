#include "Vec3D.h"

class Hit
{
	public:
		int isHit;
		Vec3Df hitPoint;
		Vec3Df normal;
		Vec3Df colour;

		Hit(int fisHit, Vec3Df fhitPoint, Vec3Df fnormal, Vec3Df fcolour){
			isHit = fisHit;
			hitPoint = fhitPoint;
			normal = fnormal;
			colour = fcolour;
		}
};

class Sphere
{
	Vec3Df sphereMidPoint;
	float sphereRadius;

	public:
		Sphere(Vec3Df midPoint, float radius){
			sphereMidPoint = midPoint;
			sphereRadius = radius;
		}

		Hit intersect(Vec3Df origin, Vec3Df dest){
				Vec3Df o = origin - sphereMidPoint;
				Vec3Df d = dest - sphereMidPoint;

				// float A = pow(d[0],2)+pow(d[1],2)+pow(d[2],2);
				// float B = 2*(d[0]*o[0] + d[1]*o[1] + d[2]*o[2]);
				// float C = pow(o[0],2)+pow(o[1],2)+pow(o[1],2)-pow(sphereRadius,2);
				float A = d[0]*d[0]+d[1]*d[1]+d[2]*d[2];
				float B = 2*(d[0]*o[0] + d[1]*o[1] + d[2]*o[2]);
				float C = o[0]*o[0]+o[1]*o[1]+o[2]*o[2]-sphereRadius*sphereRadius;

				float discriminant = B*B-4*A*C;

				if(discriminant < 0){
					return Hit(0,Vec3Df(0,0,0), Vec3Df(0,0,0), Vec3Df(0,0,0));
				} if(discriminant == 0){
					float t = (-1*B)/(2*A);
					Vec3Df hitpoint = (o+(d*t));
					Vec3Df normal = hitpoint;
					normal.normalize();
					return Hit(1, hitpoint+sphereMidPoint, normal, Vec3Df(1,0,0));
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

					return Hit(1, hitpoint+sphereMidPoint, normal, Vec3Df(1,0,0));
				}
		}
};