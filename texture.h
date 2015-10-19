#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "vec.h"
#include <string>

class Texture {
public:
  Texture() : _image(NULL) {}
  virtual ~Texture() { if (_image != NULL) delete[] _image; }

  bool load(const std::string& filepath);
  const vec3 getValue(float u, float v);

protected:
  const vec3 getPixelValue(int x, int y);

private:
  int _width, _height;
  vec3* _image;
};

#endif
