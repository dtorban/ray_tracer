// Dan Orban - CSCI 5607 - Assignment 1a

// This program takes an imput file and outputs a PPM file.
// Build the program with make.
// Program usage:
//    ray_tracer <input.txt> <output.ppm>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "vec.h"
#include "parser.h"
#include <cmath>

using namespace std;

int
main(int argc, char** argv)
{
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

  // Parse scene
  Scene scene;
  SceneParser parser;
  if (!parser.parse(fileName, scene)) {
    return 1;
  }

  // Set height and width
  int height = scene.imsize.x;
  int width = scene.imsize.y;

  // Create image array
  vec3* image = new vec3[(int)(width*height)];

  //define u and v
  vec3 u = scene.viewdir.cross(scene.updir).normalize();
  vec3 v = u.cross(scene.viewdir).normalize()*-1.0f;

  // Calculate viewing window
  float aspectRatio = (1.0*height)/width;
  float d = 1.0f;
#define PI 3.14159265359
  float w = 2.0*d*tan(scene.fovh*PI/180.0/2.0);
  float h = w/aspectRatio;
  vec3 n = scene.viewdir.normalize();
  vec3 ul = scene.eye + n*d + v*(h/2.0f) - u*(w/2.0f);
  vec3 ur = scene.eye + n*d + v*(h/2.0f) + u*(w/2.0f);
  vec3 ll = scene.eye + n*d - v*(h/2.0f) - u*(w/2.0f);
  //vec3 lr = scene.eye + n*d - v*(h/2.0f) + u*(w/2.0f);
  vec3 dh = (ur - ul)/(1.0f*width-1.0f);
  vec3 dv = (ll - ul)/(1.0f*height-1.0f);

  vec3 rayStart = scene.eye;

  // draw image
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      // Get pixel position
      vec3 pixelPos = ul+dh*x+dv*y;
      vec3 rayDir = (pixelPos-rayStart).normalize();

      // Set background color
      image[x*height + y] = scene.bkgcolor;

      // Intersect spheres
      vec3 intersect;
      bool hasValue = false;
      float t = 0.0;
      for (int f = 0; f < scene.spheres.size(); f++) {
	float newt;
	if (scene.spheres[f].intersectRay(rayStart, rayDir, intersect, newt))
	{
	  // If value is closer set pixel to this sphere color
	  if (newt > 0 && (newt < t || !hasValue)) {
	    image[x*height + y] = scene.spheres[f].mtlcolor;
	    t = newt;
	    hasValue = true;
	  }
	}
      }
    }
  }

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
      output << " " << (int)(255*image[x*height + y].r);
      output << " " << (int)(255*image[x*height + y].g);
      output << " " << (int)(255*image[x*height + y].b);
      pixelCount++;
      if (pixelCount% 5 == 0)
      {
	output << endl;
      }
    }
  }

  output.close();

  delete[] image;

  return 0;
}
