#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include "vec.h"

struct Intersect {
  vec3 point;
  Material material;
  vec3 normal;
};

class GraphicsObject {
public:
  virtual ~GraphicsObject() {}
  virtual bool intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const = 0;
};

#endif
