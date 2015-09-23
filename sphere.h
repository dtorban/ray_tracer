#ifndef SPHERE_H_
#define SPHERE_H_

#include "vec.h"

class Sphere
{
public:
  Sphere(vec3 position, float radius);
  ~Sphere();

  vec3 pos;
  float r;
  vec3 mtlcolor;

  bool intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t);
};

#endif
