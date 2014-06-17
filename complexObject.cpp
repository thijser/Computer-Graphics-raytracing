#include "complexObject.h"

ComplexObject::ComplexObject(Triangle coT, Material mat, Mesh comyMesh){
	T = coT;
	material = mat;
	myMesh = comyMesh;
}

Hit ComplexObject::intersect(Vec3Df origin, Vec3Df dest){
// Our implementation is based on the proposed algorithm of Dan Sunday at: http://geomalgorithms.com/a06-_intersect-2.html	  
	  //std::cout<<T.v[0]<<" "<<T.v[1]<<" "<<T.v[2]<<std::endl;
	  Vertex v0 = myMesh.vertices[T.v[0]];
	  Vertex v1 = myMesh.vertices[T.v[1]];
	  Vertex v2 = myMesh.vertices[T.v[2]];
	  // Edge vectors
	  Vec3Df u = v1.p-v0.p;
	  Vec3Df v = v2.p-v0.p;
	  Vec3Df n = Vec3Df::crossProduct(u, v);

	  Vec3Df w0 = origin - v0.p;
	  float a = -Vec3Df::dotProduct(n, w0);
	  float b = Vec3Df::dotProduct(n, dest);

	  // Use this as a threshold to avoid division overflow
	  float small = 0.00000001;
	  if (fabs(b) < small) {        // ray is parallel to triangle plane
	  if (a == 0)                 // ray lies in triangle plane
	    return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);
	  else
	    return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);  // ray is parallel and disjoint from plane
	  }

	  // Get intersection point of ray with triangle plane
	  float r = a / b;
	  if (r < 0.0)                  // ray goes away from triangle
	    return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);                  // Then there is no intersect

	  // intersect point of ray and plane
	  Vec3Df I = origin + (r * dest);

	  // Next up; triangle text; is I inside T?
	  float uu, uv, vv, wu, wv, D;
	  uu = Vec3Df::dotProduct(u, u);
	  uv = Vec3Df::dotProduct(u, v);
	  vv = Vec3Df::dotProduct(v, v);
	  Vec3Df w = I - v0.p;
	  wu = Vec3Df::dotProduct(w, u);
	  wv = Vec3Df::dotProduct(w, v);
	  D = uv * uv - uu * vv;

	  // get and test parametric coords
	  float s, t;
	  s = (uv * wv - vv * wu) / D;
	  if (s < 0.0 || s > 1.0)         // I is outside T
	     return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);
	  t = (uv * wu - uu * wv) / D;
	  if (t < 0.0 || (s + t) > 1.0)  // I is outside T
	     return Hit(0, Vec3Df(0,0,0), Vec3Df(0,0,0), material);

	  Vec3Df normal = I;
	  normal.normalize();

	  return Hit(1, I, normal, material);                      // I is in T
}

