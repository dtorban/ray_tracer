#ifndef SCENE_H
#define SCENE_H

#include "vec.h"

struct Scene
{
  vec3 eye;
  vec3 viewdir;
  vec3 updir;
  float fovh;
  vec2 imsize;

  vec3 bkgcolor;
};

#endif
