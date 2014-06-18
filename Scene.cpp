#include "Scene.h"

Scene::Scene(std::vector<Intersectable*> objs){
	Objects = objs;
}

Scene::Scene(){}

Hit Scene::intersect(Vec3Df origin, Vec3Df dest){
	Hit h = Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0),Material());
	float current_length = 999;

	for(int i = 0; i < Objects.size(); i++){
		Hit obj_h = Objects[i]->intersect(origin, dest);

		if(obj_h.isHit){
			Vec3Df length_vector = h.hitPoint-origin;
			float length = Vec3Df::dotProduct(length_vector, length_vector);

			if(length < current_length){
				current_length = length;
				h = obj_h;

			}
		}
	}

	return h;
}
