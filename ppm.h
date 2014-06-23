#ifndef PPM_H
#define PPM_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Vec3D.h"

using std::cout;
using std::string;

class PPM{
	string filename;
	int _width;
	int _height;

	public:
		std::vector<std::vector<Vec3Df> > image;
		PPM();
		PPM(string file_name);
		int getWidth();
		int getHeight();
		Vec3Df getPixel(int x, int y);
};

#endif