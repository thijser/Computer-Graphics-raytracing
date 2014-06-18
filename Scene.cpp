#include "Scene.h"

Scene::Scene(std::vector<Intersectable*> objs){
	Objects = objs;
}

Scene::Scene(){}

Hit Scene::intersect(Vec3Df origin, Vec3Df dest){
	Hit h = Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0),Material());

	for(int i = 0; i < Objects.size(); i++){
		Hit obj_h = Objects[i]->intersect(origin, dest);
		float current_length = 0;

		if(obj_h.isHit){
			if(!h.isHit){
				h = obj_h;
				Vec3Df length_vector = h.hitPoint-origin;
				float length = Vec3Df::dotProduct(length_vector, length_vector);
				current_length = length;
			}

			Vec3Df length_vector = dest-origin;
			float length = Vec3Df::dotProduct(length_vector, length_vector);

			if(length < current_length){
				current_length = length;
				h = obj_h;
			}
		}
	}

	return h;
}
