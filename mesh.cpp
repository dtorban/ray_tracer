#include "mesh.h"
#include <cmath>

Mesh::Mesh() : texture(NULL)
{
}

Mesh::~Mesh()
{
}

bool Mesh::intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const
{
  obj = this;

  return true;
}

Material Mesh::getMaterial(const vec3& intersect) const {
  return material;
}

vec3 Mesh::getNormal(const vec3& intersect) const {
  return vec3(1.0f);
}
