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
  bool parseVec(const std::string& name, std::stringstream& ss, vec<T>& v);
};

template <typename T>
bool SceneParser::parseVec(const std::string& name, std::stringstream& ss, vec<T>& v)
{
  int f = 0;
  std::string token;

  while(f < v.getSize() && ss >> token)
  {
    v[f] = atof(token.c_str());
    f++;
  }

  if (f != v.getSize()) {
    std::cout << "For " << name << " expected " << v.getSize() << " values but recieved " << f << std::endl;
    return false;
  }

  return true;
}

#endif
