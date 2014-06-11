#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

class Intersectable
{
	public:
		virtual std::Pair<int, Vec3Df> intersect(Vec3Df origin, Vec3Df dest);
};

#endif