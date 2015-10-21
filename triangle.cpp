#include "triangle.h"
#include <cmath>
#include "mesh.h"
#include <iostream>

Triangle::Triangle(const Mesh* mesh, const VertData& v1, const VertData& v2, const VertData& v3) : texture(NULL), _mesh(mesh)
{
  _vertData[0] = v1;
  _vertData[1] = v2;
  _vertData[2] = v3;
  material = mesh->material;
  texture = mesh->texture;

  vec3 p0 = _mesh->_vertices[v1.index-1];
  vec3 p1 = _mesh->_vertices[v2.index-1];
  vec3 p2 = _mesh->_vertices[v3.index-1];

  _edges[0] = p1-p0;
  _edges[1] = p2-p0;
  _normal = _edges[0].cross(_edges[1]).normalize();
  _planeD = _normal.dot(p0)*-1.0f;
}

Triangle::~Triangle()
{
}

bool Triangle::intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const
{
  obj = this;

  float d = _normal.dot(dir);

  if (std::abs(d) < 0.0001)
    {
      return false;
    }

  t = -(_normal.dot(start) + _planeD)/d;

  if (t < 0) {
    return false;
  }

  intersect = start + dir*t;
  vec3 barCoords = calcBarCoords(intersect);

  if (barCoords.x + barCoords.y + barCoords.z - 1 < 0.001) {
  //if (barCoords.x > 0 && barCoords.x < 1.0 && barCoords.y > 0 && barCoords.y <1.0 && barCoords.z > 0 && barCoords.z < 1.0) {
    return true;
  }

  return false;
}

float calcArea(const vec3& a, const vec3& b)
{
  return a.cross(b).length()/2.0f;
}

vec3 Triangle::calcBarCoords(const vec3& intersect) const {
  const vec3& p1 = _mesh->_vertices[_vertData[1].index-1];
  const vec3& p2 = _mesh->_vertices[_vertData[2].index-1];

  vec3 e1 = _edges[0];
  vec3 e2 = _edges[1];
  vec3 e3 = intersect-p1;
  vec3 e4 = intersect-p2;

  float A = calcArea(e1, e2);
  float a = calcArea(e3, e4);
  float b = calcArea(e4, e2);
  float c = calcArea(e1, e3);

  return vec3(a/A, b/A, c/A);
}

/*vec3 Triangle::calcBarCoords(const vec3& intersect) const {
  const vec3& p0 = _mesh->_vertices[_vertData[0].index-1];
  const vec3& p1 = _mesh->_vertices[_vertData[1].index-1];
  const vec3& p2 = _mesh->_vertices[_vertData[2].index-1];

  float a = p0.x-p1.x;
  float b = p0.y-p1.y;
  float c = p0.z-p1.z;
  float d = p0.x-p2.x;
  float e = p0.y-p2.y;
  float f = p0.z-p2.z;


  return vec3(1.0f);
  }*/

Material Triangle::getMaterial(const vec3& intersect) const {
  return material;
}

vec3 Triangle::getNormal(const vec3& intersect) const {
  return _normal;
}
