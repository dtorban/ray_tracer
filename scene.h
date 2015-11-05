#ifndef SCENE_H
#define SCENE_H

#include "vec.h"
#include "sphere.h"
#include <vector>
#include "light.h"
#include <map>
#include <string>
#include "texture.h"
#include "material.h"
#include "graphics_object.h"

struct Scene
{
  Scene() : eta(1.0), viewdist(1.0), depthOfField(false) {}
  ~Scene()
  {
    for (int f = 0; f < objects.size(); f++) {
      delete objects[f];
    }
  }

  vec3 eye;
  vec3 viewdir;
  vec3 updir;
  float fovh;
  vec2 imsize;
  bool isParallel;

  vec3 bkgcolor;
  float eta;
  float viewdist;
  bool depthOfField;

  std::vector<GraphicsObject*> objects;
  std::vector<Light> lights;
  std::map<std::string, Texture> textures;
};

#endif
