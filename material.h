#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec.h"

struct Material
{
  vec3 objectColor;
  vec3 specularColor;
  vec3 k;
  float n;
  float alpha;
  float eta;
};

#endif
