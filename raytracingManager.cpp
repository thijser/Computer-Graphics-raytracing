#include "raytracingManager.h"

#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "mesh.h"
#include "raytracing.h"
#include "image.h"
#include "rgbValue.h"


#ifdef WIN32
#include <process.h>
#else
#include <pthread.h>
#endif

std::mutex thread_counter;
int thread_count = 0;

void manageRaytracing(unsigned int WindowSize_X, unsigned int WindowSize_Y) {

	std::cout << "Raytracing" << std::endl;

	Image result(WindowSize_X, WindowSize_Y);
	Vec3Df origin00, dest00;
	Vec3Df origin01, dest01;
	Vec3Df origin10, dest10;
	Vec3Df origin11, dest11;
	Vec3Df origin, dest;


	produceRay(0, 0, &origin00, &dest00);
	produceRay(0, WindowSize_Y - 1, &origin01, &dest01);
	produceRay(WindowSize_X - 1, 0, &origin10, &dest10);
	produceRay(WindowSize_X - 1, WindowSize_Y - 1, &origin11, &dest11);

	for (unsigned int y = 0; y < WindowSize_Y; ++y)
	{
		for (unsigned int x = 0; x<WindowSize_X; ++x)
		{
			float xscale = 1.0f - float(x) / (WindowSize_X - 1);
			float yscale = float(y) / (WindowSize_Y - 1);

			origin = yscale*(xscale*origin00 + (1 - xscale)*origin10) +
				(1 - yscale)*(xscale*origin01 + (1 - xscale)*origin11);
			dest = yscale*(xscale*dest00 + (1 - xscale)*dest10) +
				(1 - yscale)*(xscale*dest01 + (1 - xscale)*dest11);


			Vec3Df rgb = performRayTracing(origin, dest);
			result.setPixel(x, y, RGBValue(rgb[0], rgb[1], rgb[2]));
			std::cout << (x + 1) / WindowSize_X << "% Complete. (" << x << "/" << WindowSize_X << ", " << y << "/" << WindowSize_Y << ")" << std::endl;
		}
	}

	result.writeImage("result.ppm");
	std::cout << "Raytracing Complete" << std::endl;
}
