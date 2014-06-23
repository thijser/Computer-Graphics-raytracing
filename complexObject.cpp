// System headers
#include <limits>
#include <algorithm>
// Our own headers
#include "./complexObject.h"
#include "./hit.h"

ComplexObject::ComplexObject(Mesh mesh) {
  this->mesh = mesh;
  Material defaultMaterial = mesh.materials.front();
  nullVector = Vec3Df(0, 0, 0);
  noHit = Hit(0, nullVector, nullVector, defaultMaterial);
  initBoundingBox();
}


void ComplexObject::initBoundingBox() {
  // Where we keep track of the following bounds
  float xMin, yMin, zMin =  std::numeric_limits<float>::max();
  float xMax, yMax, zMax = -std::numeric_limits<float>::max();

  for (int triangle = 0; triangle < mesh.triangles.size(); triangle++) {
    Triangle T = mesh.triangles[triangle];
    for (int vertex = 0; vertex < 3; vertex++) {
      Vertex V = mesh.vertices[T.v[vertex]];
      Vec3Df vertexPosition = V.p;

      // X axis
      xMin = std::min(xMin, vertexPosition[0]);
      xMax = std::max(xMax, vertexPosition[0]);
      // Y axis
      yMin = std::min(yMin, vertexPosition[1]);
      yMax = std::max(yMax, vertexPosition[1]);
      // Z axis
      zMin = std::min(zMin, vertexPosition[2]);
      zMax = std::max(zMax, vertexPosition[2]);
    }
  }
  bounds[0] = Vec3Df(xMin, yMin, zMin);
  bounds[1] = Vec3Df(xMax, yMax, zMax);
}

Hit ComplexObject::intersectBoundingBox(Vec3Df origin, Vec3Df dest) {
  // Our implementation is based on the ray-box intersection algorithm
  // as proposed here: http://people.csail.mit.edu/amy/papers/box-jgt.pdf

  // This section should be stored in a ray datastructure where it's cached
  Vec3Df direction = dest - origin;
  Vec3Df inverseDirection = Vec3Df(1/direction[0], 1/direction[1], 1/direction[2]);
  int sign[3];
  sign[0] = (inverseDirection[0] < 0);
  sign[1] = (inverseDirection[1] < 0);
  sign[2] = (inverseDirection[2] < 0);

  // Intersection algorithm
  float xMin, yMin, zMin, xMax, yMax, zMax;
  xMin = (bounds[  sign[0]  ][0] - origin[0]) * inverseDirection[0];
  xMax = (bounds[ 1-sign[0] ][0] - origin[0]) * inverseDirection[0];
  yMin = (bounds[  sign[1]  ][1] - origin[1]) * inverseDirection[1];
  yMax = (bounds[ 1-sign[1] ][1] - origin[1]) * inverseDirection[1];
  zMin = (bounds[  sign[2]  ][2] - origin[2]) * inverseDirection[2];
  zMax = (bounds[ 1-sign[2] ][2] - origin[2]) * inverseDirection[2];
  if ( (xMin > yMax) || (yMin > xMax) ) return noHit;
  if (yMin > xMin) xMin = yMin;
  if (yMax < xMax) xMax = yMax;
  if ( (xMin > zMax) || (zMin > xMax) ) return noHit;
  if (zMin > xMin) xMin = zMin;
  if (zMax < xMax) xMax = zMax;
  return Hit(1, Vec3Df(xMin, yMin, zMin), nullVector, defaultMaterial);
}

Hit ComplexObject::intersectMesh(Vec3Df origin, Vec3Df dest) {
  // hit is is where we keep track of hits with backfaces
  // For the moment we use noHit as a symbol
  Hit hit = noHit;

  for (int i = 0; i < mesh.triangles.size(); i++) {
    Triangle T = mesh.triangles[i];

    //now return the actual material which is defined in the mesh
    Material actualMat = mesh.materials.front();//mesh.materials[mesh.triangleMaterials[i]];

    // Our implementation is based on the proposed algorithm of Dan Sunday at: http://geomalgorithms.com/a06-_intersect-2.html
    Vertex v0 = mesh.vertices[T.v[0]];
    Vertex v1 = mesh.vertices[T.v[1]];
    Vertex v2 = mesh.vertices[T.v[2]];

    // Edge vectors
    Vec3Df u = v1.p-v0.p;
    Vec3Df v = v2.p-v0.p;
    Vec3Df n = Vec3Df::crossProduct(u, v);  // Normal of the triangle

    Vec3Df w0 = origin - v0.p;
    float a = -Vec3Df::dotProduct(n, w0);
    float b = Vec3Df::dotProduct(n, dest);

    // Use this as a threshold to avoid division overflow
    float small = 0.00000001;
    if (fabs(b) < small) {
      // ray is parallel to triangle plane
      if (a == 0)
        // ray lies in triangle plane
        continue;
      else
        // ray is parallel and disjoint from plane
        continue;
    }

    // Get intersection point of ray with triangle plane
    float r = a / b;
    if (r < small)  // ray goes away from triangle
      // Then there is no intersect
      continue;

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
       continue;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
       continue;

    n.normalize();  // We can now truncate the normal to length of 1

    // If we get here I (the ray hitpoint) is in T (the triangle):
    // We check if we already found a hit before
    if (hit.isHit == 0) {
      // In that case we can just assign the current hit as the first one
      hit = Hit(1, I, n, actualMat);
    } else {
      // If so, we check whether this one is closer to the origin
      float previousDistance = (hit.hitPoint - origin).getLength();
      float currentDistance  = (I - origin).getLength();

      // Now check if it's closer
      if (currentDistance < previousDistance) {
        // If it is then we save the current hit
        hit = Hit(1, I, n, actualMat);
      } else {
        // If not we discard this hit and continue looking for one which is
        continue;
      }
    }
  }
  return hit;
}
Hit ComplexObject::intersect(Vec3Df origin, Vec3Df dest) {
  Hit hit;
  hit = this->intersectBoundingBox(origin, dest);
  if (!hit.isHit)
    return noHit;
  hit = this->intersectMesh(origin, dest);
  return hit;
}

