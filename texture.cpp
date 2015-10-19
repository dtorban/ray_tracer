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

  _width = width;
  _height = height;

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

const vec3 Texture::getValue(float u, float v)
{
  float fi = u*(_width-1);
  float fj = v*(_height-1);
  float ii = (int)fi;
  float ij = (int)fj;
  float alpha = fi-ii;
  float beta = fj-ij;
  
  return getPixelValue(ij+1,ii+1)*alpha*beta +
    getPixelValue(ij+1,ii)*(1-alpha)*beta +
    getPixelValue(ij,ii+1)*(alpha)*(1-beta) +
    getPixelValue(ij,ii)*(1-alpha)*(1-beta);
}

const vec3 Texture::getPixelValue(int x, int y)
{
  return _image[x*_height+y];
}
