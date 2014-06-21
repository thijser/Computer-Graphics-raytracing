#include "Ray.h"

Ray::Ray(Vec3Df _origin, Vec3Df _dest, Vec3Df _colour, RayType _type){
	Ray(_origin, _dest, _colour, _type, Hit());
}

Ray::Ray(Vec3Df _origin, Vec3Df _dest, Vec3Df _colour, RayType _type, Hit _previous_hit){
	origin = _origin;
	dest = _dest;
	colour = _colour;
	type = _type;
	previous_hit = _previous_hit;
}

Ray Ray::reflectionVector(Hit h){
	Vec3Df relative_origin = origin-h.hitPoint;
	Vec3Df reflection_vector = relative_origin - (2*(Vec3Df::dotProduct(relative_origin, h.normal))*h.normal);
	reflection_vector += h.hitPoint;

	RayType reflect_type = REFLECTION_RAY;

	return Ray(h.hitPoint, reflection_vector, colour, reflect_type);
}