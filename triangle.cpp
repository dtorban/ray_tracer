#include "triangle.h"
#include <cmath>
#include "mesh.h"

Triangle::Triangle(const Mesh* mesh, const VertData& v1, const VertData& v2, const VertData& v3) : texture(NULL)
{
  _vertData[0] = v1;
  _vertData[1] = v2;
  _vertData[2] = v3;
  material = mesh->material;
  texture = mesh->texture;
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
