#include <stdlib.h>
#include <stdio.h>
#include "v3math.h"
int main(void)
{
    float *testVectA = (float *)malloc(sizeof(float)*3);
    float *testVectB = (float *)malloc(sizeof(float)*3);
    float *testVectDest = (float *)malloc(sizeof(float)*3);

    testVectA[0] = 1.234;
    testVectA[1] = 2.245;
    testVectA[2] = 0;

    testVectB[0] = 2.245;
    testVectB[1] = 1.234;
    testVectB[2] = 5.2;

    v3_subtract(testVectDest,testVectA,testVectB);

    printf("%.6f",v3_dot_product(testVectA,testVectB));
}