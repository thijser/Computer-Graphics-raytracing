#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include <intersectable.h>

class ComplexObject: public Intersectable {
  Material material;
  Mesh myMesh;
  Vec3Df nullVector;

  public:
    ComplexObject(Material material, Mesh comyMesh);
    Hit intersect(Vec3Df origin, Vec3Df dest);
};

#endif
