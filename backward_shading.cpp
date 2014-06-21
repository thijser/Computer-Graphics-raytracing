#include "backward_shading.h"
#include <stdlib.h>
#include "Light.h"

float max_random_shift = 0.0025;
int amount_of_rays = 3;
int max_bounce = 4;
Vec3Df black = Vec3Df(0,0,0);
Vec3Df white = Vec3Df(1,1,1);

Vec3Df diffuse(Vec3Df hitpoint, Vec3Df lightPos, Vec3Df normal, Material material){
	Vec3Df light_vector = lightPos-hitpoint;
	light_vector.normalize();
	float cosine_angle = Vec3Df::dotProduct(normal, light_vector);
	
	if(cosine_angle < 0){
		return black;
	}

	return material.Kd()*cosine_angle;
}

Vec3Df specular(Vec3Df hitpoint, Vec3Df lightPos, Vec3Df cameraPos, Vec3Df normal, Material material){
	Vec3Df light_vector = lightPos-hitpoint;
	Vec3Df camera_vector = cameraPos-hitpoint;
	light_vector.normalize();
	camera_vector.normalize();
	Vec3Df H = light_vector+camera_vector;
	H.normalize();
	float cosine_angle = std::pow(Vec3Df::dotProduct(normal, H),material.Ns());
	
	if(cosine_angle < 0){
		return black;
	}

	return material.Ks()*cosine_angle;
}

Vec3Df shoot_ray(Ray ray, Scene scene, int bounce_limit){

	if(ray.type == PRIMARY_RAY){
		Hit h = scene.intersect(ray.origin, ray.dest);
		std::vector<Light> Lights = scene.getLights();

		if(h.isHit == 1){
			//shoot shadow rays towards lights
			Vec3Df colour = h.material.Ka();

			int colour_additions = 0;

			for(int i = 0; i < Lights.size(); i++){
	    		std::vector<Vec3Df> pointLights = Lights[i].getPointLights();
	    		for(int j = 0; j < pointLights.size(); j++){
				    Vec3Df LightPosition = pointLights[j];

				    Ray shadow_ray = Ray(h.hitPoint, LightPosition, ray.colour, SHADOW_RAY, h);

				    colour += Lights[i].colour*shoot_ray(shadow_ray, scene, bounce_limit);
				    colour_additions += 1;
				}
			}

			return colour;
		}
		else if(h.isHit == 2){
		//hits light source
			return h.material.Ka();
		} 
		else {
			return black;
		}

	} else if(ray.type == SHADOW_RAY){
		Hit h = scene.intersect(ray.origin, ray.dest);
		if(h.isHit == 1){
			return ray.previous_hit.material.Ka();
		} else {	
			Vec3Df Colour = ray.previous_hit.material.Ka();			
			Colour += diffuse(ray.previous_hit.hitPoint, ray.dest, ray.previous_hit.normal, ray.previous_hit.material)/3;
			Colour += specular(ray.previous_hit.hitPoint, ray.dest, MyCameraPosition, ray.previous_hit.normal, ray.previous_hit.material)/3;

			return Colour;
		}
	}
}

Vec3Df backward_shading_routine(Scene scene, Vec3Df origin, Vec3Df dest){
	Vec3Df colour = black;

	Vec3Df super_sampled_dest = dest;
	super_sampled_dest.normalize();
	Vec3Df vec1 = Vec3Df::crossProduct(super_sampled_dest, Vec3Df(10,10,10));
	Vec3Df vec2 = Vec3Df::crossProduct(super_sampled_dest, vec1);
	vec1.normalize();
	vec2.normalize();
	vec1*=max_random_shift;
	vec2*=max_random_shift;

	super_sampled_dest -= vec1;
	super_sampled_dest -= vec2;

	for(int i = 0; i < amount_of_rays; i++){
		for(int j = 0; j < amount_of_rays; j++){
			Vec3Df t_super_sampled_dest = super_sampled_dest;
			t_super_sampled_dest += i*vec1 + j*vec2;
			t_super_sampled_dest *= dest.getLength();
		 	colour += shoot_ray(Ray(origin, t_super_sampled_dest, white, PRIMARY_RAY, Hit()), scene, max_bounce);
		 }
	}

	colour /= amount_of_rays*amount_of_rays;

	//colour = shoot_ray(Ray(origin, dest, white, PRIMARY_RAY, Hit()), scene, max_bounce);

	return colour;
}