// Dan Orban - CSCI 5607 - Assignment 0

// This program takes an imput file and outputs a PPM file.
// Build the program with make.
// Program usage:
//    ray_tracer <input.txt> <output.ppm>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "vec.h"

using namespace std;

int
main(int argc, char** argv)
{
  vec3 v;
  v.x = 1;
  v.y = 2;
  v.z = 3;
  cout << v[2] << " " << v.length() << " " << v.normalize() << " " << v*v << endl;

  // Use default file names if none are passed in
  string fileName = "input.txt";
  string outputFileName = "output.ppm";

  if (argc > 1)
  {
    fileName = argv[1];
    if (argc > 2)
    {
      outputFileName = argv[2];
    }
  }

  // Open file if exists
  ifstream file;
  file.open(fileName.c_str(), ios::in);
  if (!file)
  {
    cout << "Could not find file: " << fileName << "\n" <<endl;
    return 0;
  }

  // Get file size
  file.seekg(0, ios::end);
  streampos size = file.tellg();
  file.seekg(0, ios::beg);

  // First line must start with imsize
  char memblock[256];
  file.read(memblock, 7);
  if (string(memblock) != "imsize ")
  {
    cout << "Input file needs to start with imsize.\n" <<endl;
    return 1;
  }

  // Read in width
  int width, height;
  if (file.tellg() < size)
  {
    file >> width;
  }
  else
  {
    cout << "Missing width.\n" <<endl;
    return 1;
  }

  // Read in height
  if (file.tellg() < size)
  {
    file >> height;
  }
  else
  {
    cout << "Missing height.\n" <<endl;
    return 1;
  }

  // Make sure that the width and height are greater than 0
  if (width <= 0 || height <= 0)
  {
    cout << "Width and height must be greater than 0.\n" <<endl;
    return 1;
  }

  cout << "imsize " << width << " " << height << endl;

  file.close();

  // Output header information
  fstream output;
  output.open(outputFileName.c_str(), ios::out);
  output << "P3" << endl;
  output << width << " " << height << endl;
  output << 255 << endl;

  // Output pixels
  int pixelCount = 0;
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      output << " " << (y*255/height);
      output << " " << (x*255/width);
      float a = 1.0*y/height;
      float b = 1.0*x/height;
      output << " " << ((y/3)%2==0 && (x/5)%2==0 && a*b < 0.30  ? (height-y)*255/height : 0);
      pixelCount++;
      if (pixelCount% 5 == 0)
      {
	output << endl;
      }
    }
  }

  output.close();

  return 0;
}
