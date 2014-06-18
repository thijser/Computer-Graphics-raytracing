#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include <intersectable.h>

class ComplexObject: public Intersectable {
  Material material;
  Mesh mesh;
  Vec3Df nullVector;
  Hit noHit;

  // Bounding box
  float xMin, yMin, zMin, xMax, yMax, zMax;

  public:
    ComplexObject(Mesh mesh, Material material);
    Hit intersect(Vec3Df origin, Vec3Df dest);
    Hit intersectBoundingBox();

  private:
    void initBoundingBox();
};

#endif
