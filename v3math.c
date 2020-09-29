#include <stdio.h>
#include <stdlib.h>
#include "v3math.h"
#include <math.h>

// form v3 from a to b
void v3_from_points(float *dst, float *a, float *b){
    dst[0] = b[0] - a[0];
    dst[1] = b[1] - a[1];
    dst[2] = b[2] - a[2];
} 
void v3_add(float *dst, float *a, float *b){
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2];
}
void v3_subtract(float *dst, float *a, float *b){
    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
    dst[2] = a[2] - b[2];
}
float v3_dot_product(float *a, float *b){
    return (a[0] * b[0]) + (a[1]*b[1]) + (a[2]*b[2]);
}
void v3_cross_product(float *dst, float *a, float *b){
    float returnX = (a[1] * b[2]) - (a[2] * b[1]);
    float returnY = (a[2] * b[0]) - (a[0] * b[2]);
    float returnZ = (a[0] * b[1]) - (a[1] * b[0]);
    dst[0] = returnX;
    dst[1] = returnY;
    dst[2] = returnZ;
}

void v3_scale(float *dst, float s){
    dst[0] = dst[0] * s;
    dst[1] = dst[1] * s;
    dst[2] = dst[2] * s;    
}
 // angle between a and b
float v3_angle(float *a, float *b){
    float returnVal;
    float *aNorm = (float *)malloc(sizeof(float)*3);
    float *bNorm = (float *)malloc(sizeof(float)*3);
    v3_normalize(aNorm,a);
    v3_normalize(bNorm,b);
    returnVal = v3_dot_product(aNorm,bNorm);
    free(aNorm);
    free(bNorm);
    return acos(returnVal);
}
// angle between a and b; no cos-1
float v3_angle_quick(float *a, float *b){
    float returnVal;
    float *aNorm = (float *)malloc(sizeof(float)*3);
    float *bNorm = (float *)malloc(sizeof(float)*3);
    v3_normalize(aNorm,a);
    v3_normalize(bNorm,b);
    returnVal = v3_dot_product(aNorm,bNorm);
    free(aNorm);
    free(bNorm);
    return returnVal;
}
//Unsure if it works.
void v3_reflect(float *dst, float *v, float *n){
    float dotProd = v3_dot_product(n,v);
    float nVect[3];
    v3_normalize(nVect,n);
    dotProd = 2 * dotProd;
    v3_scale(nVect,dotProd);
    v3_subtract(dst, v, nVect);
}
float v3_length(float *a){
    float returnVal;
    returnVal = (a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]);
    returnVal = sqrt(returnVal);
    return returnVal;
}

void v3_normalize(float *dst, float *a){
    float vectLen = v3_length(a);
    dst[0] = a[0]/vectLen;
    dst[1] = a[1]/vectLen;
    dst[2] = a[2]/vectLen;
}
