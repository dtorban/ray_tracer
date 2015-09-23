#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include "scene.h"

using namespace std;

SceneParser::SceneParser() {
}

SceneParser::~SceneParser() {}

bool SceneParser::parse(const std::string& fileName, Scene& scene) {
  // Open file if exists
  ifstream file;
  file.open(fileName.c_str(), ios::in);
  if (!file)
  {
    cout << "Could not find file: " << fileName << "\n" <<endl;
    return 0;
  }

  bool isValid = true;
  vec3 mtlcolor;

  std::string   line;
  while(std::getline(file,line) && isValid)
    {
      std::stringstream lineStream(line);
      std::string token;
      while(lineStream >> token)
	{
	  cout << token << " ";
	  if (token == "eye")
	    {
	      isValid = parseVec(lineStream, scene.eye);
	    }
	  else if (token == "viewdir")
	    {
	      isValid = parseVec(lineStream, scene.viewdir);
	    }
	  else if (token == "updir")
	    {
	      isValid = parseVec(lineStream, scene.updir);
	    }
	  else if (token == "fovh")
	    {
	      if(lineStream >> token)
		{
		  scene.fovh = atof(token.c_str());
		  cout << scene.fovh;
		}
	      else
		{
		  return false;
		}
	    }
	  else if (token == "imsize")
	    {
	      isValid = parseVec(lineStream, scene.imsize);
	    }
	  else if (token == "bkgcolor")
	    {
	      isValid = parseVec(lineStream, scene.bkgcolor);
	    }
	  else if (token == "mtlcolor")
	    {
	      isValid = parseVec(lineStream, mtlcolor);
	    }
	  else if (token == "sphere")
	    {
	      vec3 pos;
	      isValid = parseVec(lineStream, pos);
	      if(lineStream >> token)
		{
		  float radius = atof(token.c_str());
		  cout << " " << radius;
		}
	      else
		{
		  return false;
		}
	    }
	  cout << endl;
	}
    }

  file.close();

  return isValid;
}
