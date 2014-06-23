#include "Ray.h"
#include <math.h>

Ray::Ray(Vec3Df _origin, Vec3Df _dest, Vec3Df _colour, RayType _type, Hit _previous_hit){
	origin = _origin;
	dest = _dest;
	colour = _colour;
	type = _type;
	previous_hit = _previous_hit;
}

Ray Ray::reflectionRay(Hit h){
	Vec3Df V = origin-h.hitPoint;
	Vec3Df reflection_vector = (2*(Vec3Df::dotProduct(V, h.normal))*h.normal) - V;
	reflection_vector += h.hitPoint;

	return Ray(h.hitPoint, reflection_vector, colour, SECONDARY_RAY, h);
}

//https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
Ray Ray::refractionRay(Hit h, float medium1, float medium2){
	float refrac_index = medium1/medium2;

	Vec3Df V = h.hitPoint - origin;
	V.normalize();
	float c1 = -Vec3Df::dotProduct(h.normal, V);

	if(c1 < 0){
		h.normal *= -1;
		c1 *= -1;
		refrac_index = 1/refrac_index;
	}
	
	// Snells law
	float c2 = sqrt( 1 - pow(refrac_index, 2) * (1 - pow(c1,2)) );

	Vec3Df refrac_ray = (refrac_index * V) + (refrac_index * c1 - c2) * h.normal;	

	return Ray(h.hitPoint, h.hitPoint + refrac_ray, colour, SECONDARY_RAY, h);
}
