#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "vec.h"
#include "material.h"
#include <string>
#include "texture.h"
#include "graphics_object.h"

class Triangle : public GraphicsObject
{
public:
  Triangle();
  ~Triangle();

  Material material;
  Texture *texture;

  bool intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const;
  Material getMaterial(const vec3& intersect) const;
  vec3 getNormal(const vec3& intersect) const;
};

#endif
