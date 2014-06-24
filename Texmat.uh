/* 
 * File:   Texmat.h
 * Author: thijs
 *
 * Created on June 23, 2014, 2:23 PM
 */
 #pragma once 

#include "ppm.h"
#ifndef TEXMAT_H
#define	TEXMAT_H

class Texmat {
public:
    Texmat();
    
    virtual ~Texmat();
    
    Vec3Df getlocalMat(float x , float y);
    void setBaseMat(const Material & mat);
    void setNormals(PPM file,int mode , float strength);
    void setDiffuse(PPM file,int mode , float strength);
    void setTransparancy(PPM file,int mode , float strength);
    void setAmbient(PPM file,int mode , float strength);
    void setReflective(PPM file,int mode , float strength);
private:
    Vec3Df getNormals(float x,float y);
    Vec3Df getDiffuse(float x, float y);
    int getTransparancy(float x , float y );
    Vec3Df getAmibnet(float x , float y);
    float getReflective (float x , float y);
}

#endif	/* TEXMAT_H */