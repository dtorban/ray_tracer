#ifndef LIGHT_H_
#define LIGHT_H_

#include "vec.h"

class Light {
public:
 Light(vec3 v, vec3 color, bool directional) : _color(color), _v(v), _directional(directional) {}
  virtual ~Light() {}

  vec3 getDirectionTo(const vec3 &pos) const;
  vec3 getColor() const { return _color; }

private:
  vec3 _color;
  vec3 _v;
  bool _directional;
};

#endif
