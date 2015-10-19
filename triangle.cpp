#include "triangle.h"
#include <cmath>

Triangle::Triangle() : texture(NULL)
{
}

Triangle::~Triangle()
{
}

bool Triangle::intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const
{
  obj = this;

  return true;
}

Material Triangle::getMaterial(const vec3& intersect) const {
  return material;
}

vec3 Triangle::getNormal(const vec3& intersect) const {
  return vec3(1.0f);
}
