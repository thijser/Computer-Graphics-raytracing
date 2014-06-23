#ifndef SCENE_H
#define SCENE_H

#include "intersectable.h"
#include "Light.h"

class Scene: public Intersectable
{
	std::vector<Intersectable*> Objects;
	std::vector<Light> Lights;

	public:
		Scene(std::vector<Intersectable*> objs, std::vector<Light> lights);
		Scene();
		Hit intersect(Vec3Df origin, Vec3Df dest);
		std::vector<Light> getLights();
};

#endif
