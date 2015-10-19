#include "texture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool Texture::load(const std::string& filepath)
{
  // Open file if exists
  ifstream file;
  file.open(filepath.c_str(), ios::in);
  if (!file)
  {
    cout << "Could not find file: " << filepath << endl;
    return false;
  }

  std::string line;

  // Read P3
  std::getline(file,line);

  // Read width and height
  int width, height;
  file >> width;
  file >> height;

  // Read precision
  float precision;
  file >> precision;

  _image = new vec3[width*height];

  float c;
  for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
	{
	  for (int f = 0; f < 3; f++)
	    {
	      file >> c;
	      _image[x*height + y][f] = c/precision;
	    }
	}
    }

  file.close();

  return true;
}
