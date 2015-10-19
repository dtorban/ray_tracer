#ifndef SPHERE_H_
#define SPHERE_H_

#include "vec.h"
#include "material.h"
#include <string>
#include "texture.h"

class Sphere
{
public:
  Sphere(vec3 position, float radius);
  ~Sphere();

  vec3 pos;
  float r;
  Material material;
  Texture *texture;

  bool intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t) const;
  vec3 getColor(const vec3& normal);
};

#endif
