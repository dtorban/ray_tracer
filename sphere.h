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
};

#endif
