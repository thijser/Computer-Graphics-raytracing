#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include "intersectable.h"

class ComplexObject: public Intersectable {
  Material material;
  Mesh mesh;
  Vec3Df nullVector;
  Hit noHit;

  // Bounding box (first vector is minimum values, second maximum)
  Vec3Df bounds[2];

  public:
    ComplexObject(Mesh mesh, Material material);
    Hit intersect(Vec3Df origin, Vec3Df dest);
    Hit intersectMesh(Vec3Df origin, Vec3Df dest);
    Hit intersectBoundingBox(Vec3Df origin, Vec3Df dest);

  private:
    void initBoundingBox();
};

#endif
