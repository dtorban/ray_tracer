#ifndef SCENE_H
#define SCENE_H

#include "vec.h"
#include "sphere.h"
#include <vector>
#include "light.h"
#include <map>
#include <string>
#include "texture.h"

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
  std::map<std::string, Texture> textures;
};

#endif
