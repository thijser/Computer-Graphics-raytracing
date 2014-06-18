#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

class Image
{
public:
	Image(int width, int height)
		: _width(width)
		, _height(height)
	{
		_image.resize(3 * _width*_height);
	}
	void setPixel(int i, int j, const RGBValue & rgb)
	{
		_image[3 * (_width*j + i)] = rgb[0];
		_image[3 * (_width*j + i) + 1] = rgb[1];
		_image[3 * (_width*j + i) + 2] = rgb[2];

	}
	std::vector<float> _image;
	int _width;
	int _height;

	bool writeImage(const char * filename);
};