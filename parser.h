#ifndef PARSER_H_
#define PARSER_H_

#include <sstream>
#include <string>
#include "scene.h"
#include <stdlib.h>

class SceneParser
{
public:
  SceneParser();
  ~SceneParser();

  bool parse(const std::string& fileName, Scene& scene);

private:
  template <typename T>
  bool parseVec(std::stringstream& ss, vec<T>& v);
};

template <typename T>
bool SceneParser::parseVec(std::stringstream& ss, vec<T>& v)
{
  int f = 0;
  std::string token;

  while(f < v.getSize() && ss >> token)
  {
    v[f] = atof(token.c_str());
    f++;
  }

  std::cout << v;

  return f == v.getSize();
}

#endif
