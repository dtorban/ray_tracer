#ifndef SPHERE_H_
#define SPHERE_H_

#include "vec.h"
#include "material.h"
#include <string>
#include "texture.h"
#include "graphics_object.h"

class Sphere : public GraphicsObject
{
public:
  Sphere(vec3 position, float radius);
  ~Sphere();

  vec3 pos;
  float r;
  Material material;
  Texture *texture;

  bool intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const;
  Material getMaterial(const vec3& intersect) const;
  vec3 getNormal(const vec3& intersect) const;
};

#endif
