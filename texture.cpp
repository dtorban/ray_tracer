#include "texture.h"
#include <iostream>
#include <fstream>

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

  file.close();

  return true;
}
