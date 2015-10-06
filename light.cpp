#include "light.h"
#include <iostream>

vec3 Light::getDirectionTo(const vec3& pos) const
{
  if (!_directional) {
    return _v.normalize()*-1.0f;
  }
  else {
    return (_v-pos).normalize();
  }
}

bool Light::isBetweenLight(const vec3 &pos, float dist) const
{
  return !_directional ? true : (_v-pos).length() > dist;
}
