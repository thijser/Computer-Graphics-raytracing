/* 
 * File:   Texmat.cpp
 * Author: thijs
 * 
 * Created on June 23, 2014, 2:23 PM
 */

#include "Texmat.h"
#include "mesh.h"
#include "ppm.h"
Texmat::Texmat() {
}
int basemat=0;
int normals=0;
int diffuse=0;
int transparacy=0;
int ambient=0;
int reflective=0;


    

    void setBaseMat(const Material & mat);
    void setNormals(PPM file,int mode , float strength);
    void setDiffuse(PPM file,int mode , float strength);
    void setTransparancy(PPM file,int mode , float strength);
    void setAmbient(PPM file,int mode , float strength);
    void setReflective(PPM file,int mode , float strength);


    Vec3Df getNormals(float x,float y);
    Vec3Df getDiffuse(float x, float y);
    int getTransparancy(float x , float y );
    Vec3Df getAmibnet(float x , float y);
    float getReflective (float x , float y);
    
    Vec3Df getlocalMat(float x , float y){
            Material mat = Material();
            mat.set_Ka(getAmibnet(x,y));
            mat.set_Kd(getDiffuse(x,y));
            mat.set_illum(getTransparancy(x,y));
            return mat;
        }
        
        
}

