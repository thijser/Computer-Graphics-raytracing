#ifndef UTILITY_METHODS_H
#define UTILITY_METHODS_H
#include <vector>
#include "Vec3D.h"
#include "mesh.h"
#include "hit.h"
#include "utility_methods.h"

//Method blingPhongSpeculair returns the blinn phong shading FACTOR at a specific point.
float blinnPhongSpecularfac(const Vec3Df & vertexPos, Vec3Df & normal,
		const Vec3Df & lightPos, const Vec3Df & cameraPos,float shininess);

//Method diffuseColour returns diffuse colour FACTOR at a position
float diffusefac(const Vec3Df & vertexPos, Vec3Df & normal,
		const Vec3Df & lightPos);

//Main function being called. Returns a colour at position using all other methods (Ambient, Speculair and Diffuse)
Vec3Df findColour2(Hit h, const Vec3Df & camera, int number,int rays); 


#endif
