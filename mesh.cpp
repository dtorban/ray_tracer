#include "mesh.h"
#include <cmath>
#include <iostream>

Mesh::Mesh() : texture(NULL)
{
}

Mesh::~Mesh()
{
}

bool Mesh::intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const
{
  float newt = 0.0;

  bool hasValue = false;

  Intersect triIntersect;

  for (int f = 0; f < _triangles.size(); f++) {
        if (_triangles[f].intersectRay(start, dir, triIntersect, newt))
	{
	  // If value is closer set pixel to this
	  if (newt > 0 && (newt < t || !hasValue)) {
	    intersect = triIntersect;
	    t = newt;
	    hasValue = true;
	  }
	}
  }

  return hasValue;
}

