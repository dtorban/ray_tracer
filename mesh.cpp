#include "mesh.h"
#include <cmath>
#include <iostream>

Mesh::Mesh() : texture(NULL)
{
}

Mesh::~Mesh()
{
}

bool Mesh::intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const
{
  float newt = 0.0;
  obj = this;

  bool hasValue = false;

  vec3 triIntersect;
  const GraphicsObject* triObj;

  for (int f = 0; f < _triangles.size(); f++) {
        if (_triangles[f].intersectRay(start, dir, triIntersect, newt, triObj))
	{
	  // If value is closer set pixel to this
	  if (newt > 0 && (newt < t || !hasValue)) {
	    intersect = triIntersect;
	    obj = triObj;
	    t = newt;
	    hasValue = true;
	  }
	}
  }

  return hasValue;
}

Material Mesh::getMaterial(const vec3& intersect) const {
  return material;
}

vec3 Mesh::getNormal(const vec3& intersect) const {
  return vec3(1.0f);
}
