#ifndef MESH_H_
#define MESH_H_

#include "vec.h"
#include "material.h"
#include <string>
#include "texture.h"
#include "graphics_object.h"
#include <vector>
#include "triangle.h"

class Mesh : public GraphicsObject
{
friend Triangle;
public:
  Mesh();
  ~Mesh();

  Material material;
  Texture *texture;

  bool intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const;

  void addVertex(const vec3& vert) { _vertices.push_back(vert); }
  void addTexCoord(const vec2& coord) { _texCoords.push_back(coord); }
  void addNormal(const vec3& normal) { _normals.push_back(normal); }
  void addTriangle(const VertData& v1, const VertData& v2, const VertData& v3) { _triangles.push_back(Triangle(this, v1, v2, v3)); }

private:
  std::vector<vec3> _vertices;
  std::vector<vec2> _texCoords;
  std::vector<vec3> _normals;
  std::vector<Triangle> _triangles;
};

#endif
