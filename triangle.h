#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "vec.h"
#include "material.h"
#include <string>
#include "texture.h"
#include "graphics_object.h"

class Mesh;

struct VertData
{
  int index;
  int texCoord;
  int normal; 
};

class Triangle : public GraphicsObject
{
public:
  Triangle(const Mesh* mesh, const VertData& v1, const VertData& v2, const VertData& v3);
  ~Triangle();

  Material material;
  Texture *texture;

  bool intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const;

private:
  const Mesh* _mesh;
  VertData _vertData[3];
  vec3 _edges[2];
  vec3 _normal;
  float _planeD;
  bool _hasTextureCoords;
  bool _hasNormals;
};

#endif
