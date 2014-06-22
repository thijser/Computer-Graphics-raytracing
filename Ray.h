#include "Vec3D.h"
#include "hit.h"

enum RayType{
	SHADOW_RAY,
	PRIMARY_RAY,
	SECONDARY_RAY
};

class Ray{

	public:		
		Vec3Df origin;
		Vec3Df dest;
		Vec3Df colour;
		RayType type;
		Hit previous_hit;

		Ray(Vec3Df origin, Vec3Df dest, Vec3Df colour, RayType type, Hit previous_hit);
		Ray reflectionRay(Hit h);
		Ray refractionRay(Hit h, float medium1, float medium2);
};