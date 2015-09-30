#include "light.h"

vec3 Light::getDirectionTo(const vec3& pos)
{
  if (_directional) {
    return _v;
  }
  else {
    return _v-pos;
  }
}
