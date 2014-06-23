#include "Ray.h"

Ray::Ray(Vec3Df _origin, Vec3Df _dest, Vec3Df _colour, RayType _type, Hit _previous_hit){
	origin = _origin;
	dest = _dest;
	colour = _colour;
	type = _type;
	previous_hit = _previous_hit;
}

Ray Ray::reflectionRay(Hit h){
	Vec3Df relative_origin = origin-h.hitPoint;
	Vec3Df reflection_vector = (2*(Vec3Df::dotProduct(relative_origin, h.normal))*h.normal) - relative_origin;
	reflection_vector += h.hitPoint;

	return Ray(h.hitPoint, reflection_vector, colour, SECONDARY_RAY, h);
}

//https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
Ray Ray::refractionRay(Hit h, float medium1, float medium2){


	float c = -Vec3Df::dotProduct( h.normal, origin-h.hitPoint);

	float refrac_index = medium1/medium2;
	float c2 = sqrt( 1 - pow(refrac_index, 2) * (1 - pow(c,2)) );

	Vec3Df refrac_ray = (refrac_index * (origin-h.hitPoint)) + h.normal*(refrac_index * c - c2);

	return Ray(h.hitPoint, refrac_ray, colour, SECONDARY_RAY, h);
}