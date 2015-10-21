#include "sphere.h"
#include <cmath>

#define PI 3.14159265359

Sphere::Sphere(vec3 position, float radius) : pos(position), r(radius), texture(NULL)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const
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
  float t1 = (-b+sqrt(disc))/(2.0f*a);

  // If discrinament is zero, return anser
  if (disc < 0.0001 && disc > -0.0001)
  {
    t = t1;
    intersect.point = start + dir*t;
    intersect.material = getMaterial(intersect.point);
    intersect.normal = getNormal(intersect.point);

    return true;
  }

  // If discrimanent is greater than zero, return closest answer
  float t2 = (-b-sqrt(disc))/(2.0f*a);
  if (t2 < t1)
  {
    t = t2;
    intersect.point = start + dir*t2;
    intersect.material = getMaterial(intersect.point);
    intersect.normal = getNormal(intersect.point);
  }

  return true;
}

Material Sphere::getMaterial(const vec3& intersect) const {
  if (texture != NULL) {
    vec3 n = getNormal(intersect);
    float theta = atan2(n.x, n.z);
    theta += PI;
    float phi = acos(n.y);
    if (theta < 0) theta += 2.0f*PI;
    theta -= 2.0f*PI*floor(theta/(2.0f*PI));
    float u = (theta)/(2.0f*PI);
    float v = phi/PI;
    Material mtl = material;
    mtl.objectColor = texture->getValue(u, v);
    return mtl;
  }
  else {
    return material;
  }

}

vec3 Sphere::getNormal(const vec3& intersect) const {
  return (intersect-pos).normalize();
}
