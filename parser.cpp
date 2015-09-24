#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include "scene.h"

using namespace std;

SceneParser::SceneParser() {
}

SceneParser::~SceneParser() {}

bool validateLength(const string& name, const vec3& v)
{
  // Ensure that the length is greater than zero
  if (v.length() == 0)
    {
      cout << name << " must have a length greater than 0" << endl;
      return false;
    }
  return true;
}

bool SceneParser::parse(const std::string& fileName, Scene& scene) {
  // Open file if exists
  ifstream file;
  file.open(fileName.c_str(), ios::in);
  if (!file)
  {
    cout << "Could not find file: " << fileName << "\n" <<endl;
    return false;
  }

  bool isValid = true;
  vec3 mtlcolor;

  // Read each line from the file and parse tokens
  std::string   line;
  while(std::getline(file,line) && isValid)
    {
      std::stringstream lineStream(line);
      std::string token;
      while(lineStream >> token)
	{
	  // Parse tokens
	  if (token == "eye")
	    {
	      isValid = parseVec(token, lineStream, scene.eye);
	    }
	  else if (token == "viewdir")
	    {
	      isValid = parseVec(token, lineStream, scene.viewdir);
	      isValid = isValid && validateLength(token, scene.viewdir);
	    }
	  else if (token == "updir")
	    {
	      isValid = parseVec(token, lineStream, scene.updir);
	      isValid = isValid && validateLength(token, scene.updir);
	    }
	  else if (token == "fovh")
	    {
	      if(lineStream >> token)
		{
		  scene.fovh = atof(token.c_str());
		  if (scene.fovh <= 0 || scene.fovh >= 180)
		    {
		      cout << token << " must be between 0 and 180." << endl;
		      isValid = false;
		    }
		}
	      else
		{
		  cout << "Missing fovh value." << endl;
		  isValid = false;
		}
	    }
	  else if (token == "imsize")
	    {
	      isValid = parseVec(token, lineStream, scene.imsize);
	      if (scene.imsize.x < 0 || scene.imsize.y < 0) {
		cout << "imsize must have positive width and height." << endl;
		isValid = false;
	      }
	    }
	  else if (token == "bkgcolor")
	    {
	      isValid = parseVec(token, lineStream, scene.bkgcolor);
	    }
	  else if (token == "mtlcolor")
	    {
	      isValid = parseVec(token, lineStream, mtlcolor);
	    }
	  else if (token == "sphere")
	    {
	      // Create sphere
	      vec3 pos;
	      isValid = parseVec(token, lineStream, pos);
	      if(lineStream >> token)
		{
		  float radius = atof(token.c_str());

		  Sphere sphere(pos, radius);
		  sphere.mtlcolor = mtlcolor;
		  scene.spheres.push_back(sphere);
		}
	      else
		{
		  cout << "Missing sphere radius." << endl;
		  isValid = false;
		}
	    }
	}
    }

  file.close();

  return isValid;
}
