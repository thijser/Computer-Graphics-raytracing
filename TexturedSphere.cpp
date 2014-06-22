#include "TexturedSphere.h"
#include <iostream>

#define MIN_T 0.0001
#define PI 3.1415926535897932384626433832795 

TexturedSphere::TexturedSphere(Vec3Df midPoint, float radius, Material mat, std::string _filename){
	sphereMidPoint = midPoint;
	sphereRadius = radius;
	material = mat;
	image = PPM(_filename);
}

Hit TexturedSphere::intersect(Vec3Df origin, Vec3Df dest){

	Vec3Df o = origin - sphereMidPoint;
	Vec3Df d = dest - sphereMidPoint;

	//dotproduct(d,d)
	float A = d[0]*d[0]+d[1]*d[1]+d[2]*d[2];

	//dotproduct(d,o) * 2
	float B = 2* (d[0]*o[0] + d[1]*o[1] + d[2]*o[2]);

	//dotproduct(o,o) - radius*radius	
	float C = o[0]*o[0]+o[1]*o[1]+o[2]*o[2]-sphereRadius*sphereRadius;

	float discriminant = B*B-4*A*C;

	if(discriminant < 0){
		return Hit(0,Vec3Df(0,0,0), Vec3Df(0,0,0), material);
	} if(discriminant == 0){
		float t = (-1*B)/(2*A);

		if(std::abs(t) < MIN_T){
			return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);
		}


		Vec3Df hitpoint = (o+(d*t));
		Vec3Df normal = hitpoint;
		normal.normalize();

		//got the following code from https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
		float phi = acos(-1*Vec3Df::dotProduct(normal,Vec3Df(0,1,0)));
		int v = float(image.getHeight())-((phi/PI)*float(image.getHeight()) );
		int u;

		float theta = acos(Vec3Df::dotProduct( normal, Vec3Df(1,0,0) ) / sin( phi ))  / ( 2.0 * PI);
		if ( Vec3Df::dotProduct(Vec3Df::crossProduct( normal, Vec3Df(1,0,0) ), normal) > 0 ){
			u = theta*image.getWidth();
		} else{ 
			u = (1 - theta)*image.getWidth();
		}

		Vec3Df pixel = image.getPixel(u,v);

		Material mat = Material(material);

		mat.set_Kd(pixel[0], pixel[1], pixel[2]);


		return Hit(1, hitpoint+sphereMidPoint, normal, mat);
	} else{
		float t;
		float t1 = ((-1*B)-sqrt(discriminant))/(2*A);
		float t2 = ((-1*B)+sqrt(discriminant))/(2*A);
		
		if(t1 < 0 && t2 < 0){			
			return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);
		} else if(t1 < 0){
			t = t2;
		} else if(t2 < 0){
			t = t1;
		} else if(t1 < t2){
			t = t1;
		} else {
			t = t2;
		}

		if(std::abs(t) < MIN_T){
			return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);
		}

		Vec3Df hitpoint = (o+(d*t));

		Vec3Df normal = hitpoint;
		normal.normalize();

		//got the following code from https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
		float phi = acos(-1*Vec3Df::dotProduct(normal,Vec3Df(0,1,0)));
		int v = float(image.getHeight())-((phi/PI)*float(image.getHeight()) );
		int u;

		float theta = acos(Vec3Df::dotProduct( normal, Vec3Df(1,0,0) ) / sin( phi ))  / ( 2.0 * PI);
		if ( Vec3Df::dotProduct(Vec3Df::crossProduct( normal, Vec3Df(1,0,0) ), normal) > 0 ){
			u = theta*image.getWidth();
		} else{ 
			u = (1 - theta)*image.getWidth();
		}

		Vec3Df pixel = image.getPixel(u,v);

		Material mat = Material(material);

		mat.set_Kd(float(pixel[0])/255.0, float(pixel[1])/255.0, float(pixel[2]/255.0));

		return Hit(1, hitpoint+sphereMidPoint, normal, mat);
	}
}
