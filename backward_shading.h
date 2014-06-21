#ifndef SIMPLE_SHADING_H
#define SIMPLE_SHADING_H

#include "Vec3D.h"
#include "mesh.h"
#include "Scene.h"
#include "initialize.h"
#include "Ray.h"

Vec3Df shoot_ray(Ray ray, Scene scene, int bounce_limit);
Vec3Df diffuse(Vec3Df hitpoint, Vec3Df lightPos, Vec3Df normal, Material material);
Vec3Df specular(Vec3Df hitpoint, Vec3Df lightPos, Vec3Df cameraPos, Vec3Df normal, Material material);
Vec3Df backward_shading_routine(Scene scene, Vec3Df origin, Vec3Df dest);

#endif
