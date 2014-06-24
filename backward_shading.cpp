#include "backward_shading.h"
#include <stdlib.h>
#include "Light.h"

float max_random_shift = 0.0025;
Vec3Df black = Vec3Df(0,0,0);
Vec3Df white = Vec3Df(1,1,1);
float air = 1;
float glass = 1.5;

Vec3Df diffuse(Vec3Df hitpoint, Vec3Df lightPos, Vec3Df normal, Material material){
Vec3Df light_vector = lightPos-hitpoint;
light_vector.normalize();
float cosine_angle = Vec3Df::dotProduct(normal, light_vector);

if(cosine_angle < 0){
return black;
}

return material.Kd()*cosine_angle;
//return Texture3D(hitpoint)*cosine_angle;
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

Vec3Df Texture3D(Vec3Df point){
float length = point.getLength();
float fragments = 1.0/80;
int step = 1;

Vec3Df colour = Vec3Df(1,1,0);
while(length > fragments){
length -= fragments;
switch(step){
case 0:
colour = Vec3Df(1,1,0);
step += 1;
break;
case 1:
colour = Vec3Df(0,1,0);
step += 1;
break;
case 2:
colour = Vec3Df(0,1,1);
step += 1;
break;
case 3:
colour = Vec3Df(0,0,1);
step += 1;
break;
case 4:
colour = Vec3Df(1,0,1);
step += 1;
break;
case 5:
colour = Vec3Df(1,0,0);
step = 0;
break;
}
}

switch(step){
case 0:	
colour = Vec3Df(1,(1.0/fragments)*length,0);
break;
case 1:	
colour = Vec3Df(1-(1.0/fragments)*length,1,0);
break;
case 2:
colour = Vec3Df(0,1,(1.0/fragments)*length);
break;
case 3:
colour = Vec3Df(0,1-(1.0/fragments)*length, 1);
break;
case 4:
colour = Vec3Df((1.0/fragments)*length,0,1);
break;
case 5:	
colour = Vec3Df(1,0,1-(1.0/fragments)*length);
break;
}

return colour;
}

Vec3Df shoot_ray(Ray ray, Scene scene, int bounce_limit){
//Test

if(ray.type == PRIMARY_RAY || ray.type == SECONDARY_RAY){
Hit h = scene.intersect(ray.origin, ray.dest);
std::vector<Light> Lights = scene.getLights();

if(h.isHit == 1){
            float invref = 1; //inverse reflection
            Vec3Df colour = h.material.Ka();
if(h.material.Tr() > 0.001 && h.material.Tr() <= 3){
                invref=1;//-h.material.Tr();
colour =colour+shoot_ray(ray.reflectionRay(h), scene, bounce_limit-1);
}


if(h.material.Tr() > 3){
if(Vec3Df::dotProduct(ray.dest-ray.origin, h.normal) < 0){
return shoot_ray(ray.refractionRay(h, air, glass), scene, bounce_limit-1);
} else {	
Hit new_h = Hit(h.isHit, h.hitPoint, h.normal*-1, h.material);
return shoot_ray(ray.refractionRay(new_h, glass, air), scene, bounce_limit-1);
}
}

//shoot shadow rays towards lights


int colour_additions = 0;

for(int i = 0; i < Lights.size(); i++){
std::vector<Vec3Df> pointLights = Lights[i].getPointLights();
for(int j = 0; j < pointLights.size(); j++){
Vec3Df LightPosition = pointLights[j];

//std::cout << LightPosition[0] << " " << LightPosition[1] << " " << LightPosition[2] << "\n";

Ray shadow_ray = Ray(h.hitPoint, LightPosition, ray.colour, SHADOW_RAY, h);

colour += invref*Lights[i].colour*shoot_ray(shadow_ray, scene, bounce_limit);
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
if(h.material.Tr() > 3){
if(Vec3Df::dotProduct(ray.dest-ray.origin, h.normal) < 0){
Ray refrac = ray.refractionRay(h, air, glass);
refrac.setLight(ray.dest);
return shoot_ray(refrac, scene, bounce_limit-1);
} else {	
return shoot_ray(Ray(h.hitPoint, ray.light, ray.colour, SHADOW_RAY, h), scene, bounce_limit);
}
}
return ray.previous_hit.material.Ka();
} else {	
Vec3Df Colour = ray.previous_hit.material.Ka();	
Colour += diffuse(ray.previous_hit.hitPoint, ray.dest, ray.previous_hit.normal, ray.previous_hit.material);
Colour += specular(ray.previous_hit.hitPoint, ray.dest, MyCameraPosition, ray.previous_hit.normal, ray.previous_hit.material);

return Colour/3;
}
}
}

Vec3Df backward_shading_routine(Scene scene, Vec3Df origin, Vec3Df dest){

// Hit h = Hit(1, Vec3Df(0,0,0), Vec3Df(0,1,0), Material());
// Ray d = Ray(Vec3Df(-1,1,0), Vec3Df(0,0,0), Vec3Df(1,1,1), PRIMARY_RAY, Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), Material()));
// Ray x = d.reflectionRay(h);
// std::cout << x.dest[0] << " " << x.dest[1] << " " << x.dest[2] << "\n";

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

for(int i = 0; i < config.raysPerPixelD; i++){
for(int j = 0; j < config.raysPerPixelD; j++){
Vec3Df t_super_sampled_dest = super_sampled_dest;
t_super_sampled_dest += i*vec1 + j*vec2;
t_super_sampled_dest *= dest.getLength();
colour += shoot_ray(Ray(origin, t_super_sampled_dest, white, PRIMARY_RAY, Hit()), scene, config.maxBounces);
}
}

colour /= config.raysPerPixelD*config.raysPerPixelD;

//colour = shoot_ray(Ray(origin, dest, white, PRIMARY_RAY, Hit()), scene, config.maxBounces);

return colour;
}
