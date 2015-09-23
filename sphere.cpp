#include "sphere.h"
#include <cmath>

Sphere::Sphere(vec3 position, float radius) : pos(position), r(radius)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t)
{
  float a = 1;
  vec3 dist = start-pos;
  float b = 2.0*(dir.dot(dist));
  float c = dist.dot(dist) - r*r;

  float disc = b*b-4.0*a*c;

  if (disc < 0)
  {
    return false;
  }
  
  float t1 = -b+sqrt(disc);
  intersect = start + dir*t;

  if (disc == 0)
  {
    t = t1;
    return true;
  }

  float t2 = -b-sqrt(disc);
  if (t2 < t1)
  {
    t = t2;
    intersect = start + dir*t2;
  }

  return true;
}
