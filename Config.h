#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string>

class Config {
  public:
    char * description;
    int renderSize_X;
    int renderSize_Y;
    int viewportSize_X;
    int viewportSize_Y;
    int raysPerPixelD;
    int maxBounces;

    inline Config(void) {
      description =         "Standard";
      renderSize_X =        800;
      renderSize_Y =        800;
      viewportSize_X =      800;
      viewportSize_Y =      800;
      raysPerPixelD =       3;
      maxBounces =          4;
    }

    Config(char * fDescription, int outputX, int outputY, int viewportX, int viewportY, int fRaysPerPixelD, int fMaxBounces){
      description = fDescription;
      renderSize_X = outputX;
      renderSize_Y = outputY;
      viewportSize_X = viewportX;
      viewportSize_Y = viewportY;
      raysPerPixelD = fRaysPerPixelD;
      maxBounces = fMaxBounces;
    }

    inline std::string toString() {
      int maxLength = 500;
      char * format = "Config( '%s', %dx%d, rays per pixel: %d, max bounces: %d)";
      char config[maxLength];
      snprintf(config, maxLength, format, description, renderSize_X, renderSize_Y, (raysPerPixelD*raysPerPixelD), maxBounces);
      return config;
    }
};

#endif
