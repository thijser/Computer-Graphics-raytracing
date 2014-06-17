#include <complexObject.h>

ComplexObject::ComplexObject(Material mat, Mesh comyMesh) {
  material = mat;
  myMesh = comyMesh;
  nullVector = Vec3Df(0, 0, 0);
}

Hit ComplexObject::intersect(Vec3Df origin, Vec3Df dest) {
  Hit noHit = Hit(0, nullVector, nullVector, material);
  // hit is is where we keep track of hits with backfaces
  // For the moment we use noHit as a symbol
  Hit hit = noHit;

  for (int i = 0; i < myMesh.triangles.size(); i++) {
    Triangle T = myMesh.triangles[i];
    // Our implementation is based on the proposed algorithm of Dan Sunday at: http://geomalgorithms.com/a06-_intersect-2.html
    Vertex v0 = myMesh.vertices[T.v[0]];
    Vertex v1 = myMesh.vertices[T.v[1]];
    Vertex v2 = myMesh.vertices[T.v[2]];
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
    if (r < 0.0)  // ray goes away from triangle
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
      hit = Hit(1, I, n, material);
    } else {
      // If so, we check whether this one is closer to the origin
      int previousDistance = (hit.hitPoint - origin).getLength();
      int currentDistance  = (I - origin).getLength();
      // Now check if it's closer
      if (currentDistance < previousDistance) {
        // If it is then we save the current hit
        hit = Hit(1, I, n, material);
        std::cout << "newhit" << std::endl;
      } else {
        // If not we discard this hit and continue looking for one which is
        continue;
      }
    }
  }
  return hit;
}

