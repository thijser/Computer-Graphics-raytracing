#ifndef SCENE_H
#define SCENE_H

#include "intersectable.h"

class Scene: public Intersectable
{
	std::vector<Intersectable*> Objects;

	public:
		Scene(std::vector<Intersectable*> objs);
		Scene();
		Hit intersect(Vec3Df origin, Vec3Df dest);
};

#endif
