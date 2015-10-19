#ifndef SCENE_H
#define SCENE_H

#include "vec.h"
#include "sphere.h"
#include <vector>
#include "light.h"

struct Scene
{
  vec3 eye;
  vec3 viewdir;
  vec3 updir;
  float fovh;
  vec2 imsize;
  bool isParallel;

  vec3 bkgcolor;

  std::vector<Sphere> spheres;
  std::vector<Light> lights;
};

#endif
