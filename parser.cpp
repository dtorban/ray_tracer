#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include "scene.h"
#include "material.h"
#include "mesh.h"

using namespace std;

SceneParser::SceneParser() {
}

SceneParser::~SceneParser() {}

bool parseVertexData(const std::string& str, VertData& vertData);

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

  scene.isParallel = false;
  bool isValid = true;
  Material material;
  std::string textureName;
  Mesh* mesh = new Mesh();
  scene.objects.push_back(mesh);

  // Read each line from the file and parse tokens
  std::string   line;
  while(std::getline(file,line) && isValid)
    {
      std::stringstream lineStream(line);
      std::string token = "";
      while(lineStream >> token)
	{
	  // Parse tokens
	  if (token == "eye")
	    {
	      isValid = parseVec(token, lineStream, scene.eye);
	    }
	  if (token == "parallel")
	    {
	      scene.isParallel = true;
	    }
	  else if (token == "viewdir")
	    {
	      isValid = parseVec(token, lineStream, scene.viewdir);
	      isValid = isValid && validateLength(token, scene.viewdir);
	      if(isValid) scene.viewdir = scene.viewdir.normalize();
	    }
	  else if (token == "updir")
	    {
	      isValid = parseVec(token, lineStream, scene.updir);
	      isValid = isValid && validateLength(token, scene.updir);
	      if(isValid) scene.updir = scene.updir.normalize();
	    }
	  else if (token == "fovh")
	    {
	      if(lineStream >> token)
		{
		  scene.fovh = atof(token.c_str());
		  if (scene.fovh <= 0 || scene.fovh >= 180)
		    {
		      cout << "fovh must be between 0 and 180." << endl;
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
	      isValid = parseVec(token, lineStream, material.objectColor);
	      isValid = isValid && validateLength(token, material.objectColor);
	      isValid = parseVec(token, lineStream, material.specularColor);
	      isValid = isValid && validateLength(token, material.specularColor);
	      isValid = parseVec(token, lineStream, material.k);
	      isValid = isValid && validateLength(token, material.k);
	      if(lineStream >> token)
		{
		  material.n = atof(token.c_str());
                    if (material.n < 0)
		    {
		      cout << "Material n must be greater than 0." << endl;
		      isValid = false;
		    }
		}
	      else
		{
		  cout << "Missing material n value." << endl;
		  isValid = false;
		}
	      if (isValid) {
		mesh->material = material;
	      }
	    }
	  else if (token == "sphere")
	    {
	      // Create sphere
	      vec3 pos;
	      isValid = parseVec(token, lineStream, pos);
	      if(lineStream >> token)
		{
		  float radius = atof(token.c_str());

		  Sphere* sphere = new Sphere(pos, radius);
		  sphere->material = material;
		  sphere->texture = textureName != "" ? &(scene.textures[textureName]) : NULL;
		  scene.objects.push_back(sphere);
		}
	      else
		{
		  cout << "Missing sphere radius." << endl;
		  isValid = false;
		}
	    }
	  else if (token == "light") {
	    vec4 v;
	    isValid = parseVec(token, lineStream, v);
	    vec3 color;
	    isValid = parseVec(token, lineStream, color);
	    isValid = isValid && validateLength(token, color);
	    bool directional = v.w < 1.0001 && v.w > 0.99999;
	    Light light(v, color, directional);
	    scene.lights.push_back(light);
	  }
	  else if (token == "texture")
	    {
	      if(lineStream >> token)
		{
		  textureName = token;
		  if (scene.textures.find(token) == scene.textures.end())
		    {
		      scene.textures[token] = Texture();
		      isValid = scene.textures[token].load(token);
		    }
		}
	      else
		{
		  textureName = "";
		}
	      if (isValid) {
		mesh->texture = textureName != "" ? &(scene.textures[textureName]) : NULL;
	      }
	    }
	  else if (token == "v")
	    {
	      vec3 vert;
	      isValid = parseVec(token, lineStream, vert);
	      mesh->addVertex(vert);
	      std::cout << vert << std::endl;
	    }
	  else if (token == "vt")
	    {
	      vec2 texCoord;
	      isValid = parseVec(token, lineStream, texCoord);
	      if (texCoord.x < 0 || texCoord.x > 1 || texCoord.y < 0 || texCoord.y > 0) {
		isValid = false;
		cout << "Texture coordinates must be between 0 and 1." << endl;
	      }
	      mesh->addTexCoord(texCoord);
	    }
	  else if (token == "vn")
	    {
	      vec3 normal;
	      isValid = parseVec(token, lineStream, normal);
	      mesh->addNormal(normal);
	    }
	  else if (token == "f")
	    {
	      VertData v1, v2, v3;
	      if(lineStream >> token) {
		isValid = parseVertexData(token, v1);
	      }
	      if(isValid && lineStream >> token) {
		isValid = parseVertexData(token, v2);
	      }
	      if(isValid && lineStream >> token) {
		isValid = parseVertexData(token, v3);
	      }
	      
	      if (isValid) {
		mesh->addTriangle(v1, v2, v3);
	      }

	    }
	}
    }

  file.close();

  return isValid;
}

bool parseVertexData(const std::string& str, VertData& vertData) {
  int found = str.find('/');

  vertData.texCoord = -1;
  vertData.normal = -1;

  if (found!=std::string::npos) {
    vertData.index = atof(str.substr(0,found).c_str());
    
    string sstr = str.substr(found+1, str.size() - (found + 1));
    found = sstr.find('/');

    if (found == std::string::npos) {
      cout << "Vertex face formatted incorrectly." << endl;
      return false;
    }

    if (found > 0) {
      vertData.texCoord = atof(sstr.substr(0,found).c_str());
    }

    vertData.normal = atof(sstr.substr(found+1,sstr.size() - (found+1)).c_str());
  }
  else {
    vertData.index = atof(str.c_str());
  }

  return true;
}
