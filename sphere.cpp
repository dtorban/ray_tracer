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
  // Calculate a, b, and c for quadratic formula
  float a = 1;
  vec3 dist = start-pos;
  float b = 2.0*(dir.dot(dist));
  float c = dist.dot(dist) - r*r;

  // Calculate discrinament
  float disc = b*b-4.0*a*c;

  // If the discriminant is negative, there is no intersection
  if (disc < 0)
  {
    return false;
  }
  
  // Calculate first solution of quadratic formula
  float t1 = -b+sqrt(disc);
  intersect = start + dir*t;

  // If discrinament is zero, return anser
  if (disc < 0.0001 && disc > -0.0001)
  {
    t = t1;
    return true;
  }

  // If discrimanent is greater than zero, return closest answer
  float t2 = -b-sqrt(disc);
  if (t2 < t1)
  {
    t = t2;
    intersect = start + dir*t2;
  }

  return true;
}
