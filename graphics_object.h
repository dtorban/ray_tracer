#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include "vec.h"

class GraphicsObject {
public:
  virtual ~GraphicsObject() {}
  virtual bool intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const = 0;
  virtual Material getMaterial(const vec3& intersect) const = 0;
  virtual vec3 getNormal(const vec3& intersect) const = 0;
};

#endif
