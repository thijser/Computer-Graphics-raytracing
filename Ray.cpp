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

void Ray::pprint(){
	std::cout << "Origin: " << origin[0] << " " << origin[1] << " " << origin[2] <<"\n";
	std::cout << "Dest: " << dest[0] << " " << dest[2] << " " << dest[2] << "\n";
	std::cout << "Colour: " << colour[0] << " " << colour[1] << " " << colour[2] << "\n";
	std::cout << "Type: " << type << "\n";
	std::cout << '\n'; 
}

//https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
Ray Ray::refractionRay(Hit h, float n1, float n2){
	// float refrac_index = medium1/medium2;

	// Vec3Df V = h.hitPoint - origin;
	// float c1 = -Vec3Df::dotProduct(h.normal, V);
	
	// // Snells law
	// float c2 = sqrt( 1 - pow(refrac_index, 2) * (1 - pow(c1,2)) );

	// Vec3Df refrac_ray = (refrac_index * V) + (refrac_index * c1 - c2) * h.normal;	

	// Ray r = Ray(h.hitPoint, h.hitPoint + refrac_ray, colour, SECONDARY_RAY, h);
	// std::cout << "REFRACTION ";
	// r.pprint();
	// return r;

	//http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf

	Vec3Df n = h.normal;
	Vec3Df i = dest-origin;
	float rindex = n1/n2;
	float cosoi = Vec3Df::dotProduct(i,n);
	float sin2ot = rindex*rindex*(1-(cosoi*cosoi));	
	Vec3Df t = i*rindex + (rindex*cosoi - sqrt(1-(sin2ot)))*n;

	return Ray(h.hitPoint, h.hitPoint+t, colour, type, h);
}
