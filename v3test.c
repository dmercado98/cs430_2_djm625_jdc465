#include <stdlib.h>
#include <stdio.h>
#include "v3math.h"

// int test_from_points(float *dst, float *a, float *b){

// }
// int test_add(float *dst, float *a, float *b);
// int test_subtract(float *dst, float *a, float *b);
// int test_dot_product(float *a, float *b);
// int test_cross_product(float *dst, float *a, float *b);
// int test_scale(float *dst, float s);
// int test_angle(float *dst, float *a, float *b); // angle between a and b
// int test_angle_quick(float *dst, float *a, float *b); // angle between a and b; no cos-1
// int test_reflect(float *dst, float *v, float *n);
// int test_length(float *a);
// int test_normalize(float *dst, float *a);

int main(void)
{
    float *testVectA = (float *)malloc(sizeof(float)*3);
    float *testVectB = (float *)malloc(sizeof(float)*3);
    float *testVectDest = (float *)malloc(sizeof(float)*3);

    testVectA[0] = 0;
    testVectA[1] = 7;
    testVectA[2] = 0;

    testVectB[0] = 7;
    testVectB[1] = 0;
    testVectB[2] = 0;

    printf("%.6f",v3_angle(testVectA,testVectB));
}