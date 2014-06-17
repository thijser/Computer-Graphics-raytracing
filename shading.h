#ifndef UTILITY_METHODS_H
#define UTILITY_METHODS_H
#include <vector>
#include "Vec3D.h"
#include "mesh.h"
#include "hit.h"
#include "utility_methods.h"

//Method blingPhongSpeculair returns the blinn phong shading at a specific point.
Vec3Df blingPhongSpeculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view, const Vec3Df & Lightposition,const Vec3Df & LightColour);

//Method speculair returns speculair (including shade and slight reflection of surroundings)
Vec3Df speculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view, int number);

//Method diffuseColour returns diffuse colour at a position
Vec3Df diffuseColour(Material & mat, const Vec3Df & position,
		const Vec3Df & normal, int number);

//Method lightbasedSpeculair returns colour at position includes blinn phong
Vec3Df lightbasedSpeculair(Material mat, const Vec3Df & position, const Vec3Df & normal,
		const Vec3Df & view);

//Main function being called. Returns a colour at position using all other methods
Vec3Df findColour(Hit h, const Vec3Df & camera, int number);

#endif
