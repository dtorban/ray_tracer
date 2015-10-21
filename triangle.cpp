#include "triangle.h"
#include <cmath>
#include "mesh.h"
#include <iostream>

Triangle::Triangle(const Mesh* mesh, const VertData& v1, const VertData& v2, const VertData& v3) : texture(NULL), _mesh(mesh)
{
  _hasNormals= v1.normal > 0 && v2.normal > 0 && v3.normal > 0;
  _hasTextureCoords = v1.texCoord > 0 && v2.texCoord > 0 && v3.texCoord > 0;

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

//bool Triangle::intersectRay(const vec3& start, const vec3& dir, vec3& intersect, float& t, const GraphicsObject*& obj) const
bool Triangle::intersectRay(const vec3& start, const vec3& dir, Intersect& intersect, float& t) const
{

  const vec3& p0 = _mesh->_vertices[_vertData[0].index-1];
  const vec3& p1 = _mesh->_vertices[_vertData[1].index-1];
  const vec3& p2 = _mesh->_vertices[_vertData[2].index-1];

  float a = p0.x-p1.x;
  float b = p0.y-p1.y;
  float c = p0.z-p1.z;
  float d = p0.x-p2.x;
  float e = p0.y-p2.y;
  float f = p0.z-p2.z;
  float g = dir.x;
  float h = dir.y;
  float i = dir.z;
  float j = p0.x-start.x;
  float k = p0.y-start.y;
  float l = p0.z-start.z;
  float m = e*i-h*f;
  float n = g*f-d*i;
  float o = d*h-e*g;
  float p = a*k-j*b;
  float q = j*c-a*l;
  float r = b*l-k*c;
  float s = a*m+b*n+c*o;

  if (std::abs(s) < 0.0001) {
    return false;
  }

  t = -(f*p+e*q+d*r)/s;

  if (t < 0.01) {
    return false;
  }

  float gama = (i*p+h*q+g*r)/s;

  if (gama <= 0 || gama >= 1) {
    return false;
  }

  float beta = (j*m+k*n+l*o)/s;

  if (beta <= 0 || beta >= 1 - gama) {
    return false;
  }

  float alpha = 1 - (beta + gama);

  intersect.point = start + dir*t;
  intersect.normal = _normal;
  intersect.material = material;

  if (texture != NULL && _hasTextureCoords) {
    vec2 t0 = _mesh->_texCoords[_vertData[0].texCoord-1];
    vec2 t1 = _mesh->_texCoords[_vertData[1].texCoord-1];
    vec2 t2 = _mesh->_texCoords[_vertData[2].texCoord-1];
    float u =alpha*t0.x + beta*t1.x + gama*t2.x;
    float v =alpha*t0.y + beta*t1.y + gama*t2.y;
    intersect.material.objectColor = texture->getValue(u, v);
  }

  if (_hasNormals) {
    vec3 n0 = _mesh->_normals[_vertData[0].normal-1];
    vec3 n1 = _mesh->_normals[_vertData[1].normal-1];
    vec3 n2 = _mesh->_normals[_vertData[2].normal-1];
    vec3 normal =n0*alpha + n1*beta + n2*gama;
    intersect.normal = normal.normalize();
  }

  return true;
}

