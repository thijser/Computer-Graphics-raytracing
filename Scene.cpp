#include "Scene.h"

Scene::Scene(std::vector<Intersectable*> objs, std::vector<Light> lights){
	Objects = objs;
	Lights = lights;
}

Scene::Scene(){}

std::vector<Light> Scene::getLights(){
	return Lights;
}

Hit Scene::intersect(Vec3Df origin, Vec3Df dest){
	Hit h = Hit(0, Vec3Df(0,0,0),Vec3Df(0,0,0),Material());
	float current_length = 0;

	for(int i = 0; i < Objects.size(); i++){
		Hit obj_h = Objects[i]->intersect(origin, dest);

		if(obj_h.isHit){
			Vec3Df length_vector = obj_h.hitPoint-origin;
			float length = Vec3Df::dotProduct(length_vector, length_vector);

			if(!h.isHit || length < current_length){
				current_length = length;
				h = obj_h;
			}
		}
	}

	for(int i; i < Lights.size(); i++){
		Hit l_h = Lights[i].intersect(origin,dest);
		if(l_h.isHit){			
			Vec3Df length_vector = l_h.hitPoint-origin;
			float length = Vec3Df::dotProduct(length_vector, length_vector);

			if(!h.isHit || length < current_length){
				current_length = length;
				h = l_h;
			}
		}
	}

	return h;
}
