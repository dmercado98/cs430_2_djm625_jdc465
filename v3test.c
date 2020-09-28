#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "v3math.h"

int v3_equals(float *a, float *b, float tolerance);
int v3_val_equals(float a, float b, float tolerance);
void test_from_points(float *dst, float *a, float *b);
void test_add(float *dst, float *a, float *b);
void test_subtract(float *dst, float *a, float *b);
void test_dot_product(float *a, float *b);
void test_cross_product(float *dst, float *a, float *b);
// int test_scale(float *dst, float s);
// int test_angle(float *dst, float *a, float *b); // angle between a and b
// int test_angle_quick(float *dst, float *a, float *b); // angle between a and b; no cos-1
// int test_reflect(float *dst, float *v, float *n);
// int test_length(float *a);
// int test_normalize(float *dst, float *a);

int main(void) {
    float *testVectA = (float *)malloc(sizeof(float)*3);
    float *testVectB = (float *)malloc(sizeof(float)*3);
    float *testVectDest = (float *)malloc(sizeof(float)*3);
    
    printf("\ntest from points:\n");
    test_from_points(testVectDest, testVectA, testVectB);
    
    printf("\ntest add:\n");
    test_add(testVectDest, testVectA, testVectB);
    
    printf("\ntest subtract:\n");
    test_subtract(testVectDest, testVectA, testVectB);
    
    printf("\ntest dot product:\n");
    test_dot_product(testVectA, testVectB);
    
    printf("\ntest cross product:\n");
    
    printf("\ntest scale:\n");
    
    printf("\ntest angle:\n");
    
    printf("\ntest angle quick:\n");
    
    printf("\ntest reflect:\n");
    
    printf("\ntest length\n");
    
    printf("\ntest normalize\n");
}

int v3_equals(float *a, float *b, float tolerance) {
    float x, y, z;
    x = abs(a[0] - b[0]);
    y = abs(a[1] - b[1]);
    z = abs(a[2] - b[2]);
    
    return (x <= tolerance && y <= tolerance && z <= tolerance);
}

int v3_val_equals(float a, float b, float tolerance) {
    return abs(a - b) < tolerance;
}

void test_from_points(float *dst, float *a, float *b) {
    float cv[3];
    
    // pos int test
    a[0] = 0.0;
    a[1] = 7.0;
    a[2] = 2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = 7.0;
    cv[1] = -7.0;
    cv[2] = 0.0;
    
    v3_from_points(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg int test
    a[0] = 0.0;
    a[1] = -7.0;
    a[2] = -2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = 7.0;
    cv[1] = 7.0;
    cv[2] = 4.0;
    
    v3_from_points(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // zero test
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    
    v3_from_points(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // pos float test
    a[0] = 0.0;
    a[1] = 7.12345;
    a[2] = 2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = 7.12345;
    cv[1] = -7.12345;
    cv[2] = 0.12345;
    
    v3_from_points(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos float: passed\n");
    }
    else {
        printf("pos float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg float test
    a[0] = 0.0;
    a[1] = -7.12345;
    a[2] = -2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = 7.12345;
    cv[1] = 7.12345;
    cv[2] = 4.12345;
    
    v3_from_points(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
}

void test_add(float *dst, float *a, float *b) {
    float cv[3];
    
    // pos int test
    a[0] = 0.0;
    a[1] = 7.0;
    a[2] = 2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = 7.0;
    cv[1] = 7.0;
    cv[2] = 4.0;
    
    v3_add(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg int test
    a[0] = 0.0;
    a[1] = -7.0;
    a[2] = -2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = 7.0;
    cv[1] = -7.0;
    cv[2] = 0.0;
    
    v3_add(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // zero test
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    
    v3_add(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // pos float test
    a[0] = 0.0;
    a[1] = 7.12345;
    a[2] = 2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = 7.12345;
    cv[1] = 7.12345;
    cv[2] = 4.12345;
    
    v3_add(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos float: passed\n");
    }
    else {
        printf("pos float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg float test
    a[0] = 0.0;
    a[1] = -7.12345;
    a[2] = -2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = 7.12345;
    cv[1] = -7.12345;
    cv[2] = 0.12345;
    
    v3_add(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
}

void test_subtract(float *dst, float *a, float *b) {
    float cv[3];
    
    // pos int test
    a[0] = 0.0;
    a[1] = 7.0;
    a[2] = 2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = -7.0;
    cv[1] = 7.0;
    cv[2] = 0.0;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg int test
    a[0] = 0.0;
    a[1] = -7.0;
    a[2] = -2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = -7.0;
    cv[1] = -7.0;
    cv[2] = -4.0;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // zero test
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // pos float test
    a[0] = 0.0;
    a[1] = 7.12345;
    a[2] = 2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = -7.12345;
    cv[1] = 7.12345;
    cv[2] = -0.12345;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos float: passed\n");
    }
    else {
        printf("pos float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg float test
    a[0] = 0.0;
    a[1] = -7.12345;
    a[2] = -2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = -7.12345;
    cv[1] = -7.12345;
    cv[2] = -4.12345;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
}

void test_dot_product(float *a, float *b){
    float cv;
    float v;
    
    // pos int test
    a[0] = 0.0;
    a[1] = 7.0;
    a[2] = 2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv = 4;
    
    v = v3_dot_product(a, b);
    
    if(v3_val_equals(v, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: %.6f\n", cv);
        printf("\tactual: %.6f\n", v);
    }
    
    // neg int test
    a[0] = 0.0;
    a[1] = -7.0;
    a[2] = -2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv = -4;
    
    v = v3_dot_product(a, b);
    
    if(v3_val_equals(v, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: %.6f\n", cv);
        printf("\tactual: %.6f\n", v);
    }
    
    // zero test
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;
    
    cv = 0;
    
    v = v3_dot_product(a, b);
    
    if(v3_val_equals(v, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: %.6f\n", cv);
        printf("\tactual: %.6f\n", v);
    }
    
    // pos float test
    a[0] = 0.0;
    a[1] = 7.12345;
    a[2] = 2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv = 4.2469;
    
    v = v3_dot_product(a, b);
    
    if(v3_val_equals(v, cv, 0.0001)) {
        printf("pos float: passed\n");
    }
    else {
        printf("pos float: failed\n");
        printf("\texpected: %.6f\n", cv);
        printf("\tactual: %.6f\n", v);
    }
    
    // neg float test
    a[0] = 0.0;
    a[1] = -7.12345;
    a[2] = -2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv = -4.2469;
    
    v = v3_dot_product(a, b);
    
    if(v3_val_equals(v, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: %.6f\n", cv);
        printf("\tactual: %.6f\n", v);
    }
}

void test_cross_product(float *dst, float *a, float *b) {
    float cv[3];
    
    // pos int test
    a[0] = 0.0;
    a[1] = 7.0;
    a[2] = 2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = -7.0;
    cv[1] = 7.0;
    cv[2] = 0.0;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg int test
    a[0] = 0.0;
    a[1] = -7.0;
    a[2] = -2.0;
    
    b[0] = 7.0;
    b[1] = 0.0;
    b[2] = 2.0;
    
    cv[0] = -7.0;
    cv[1] = -7.0;
    cv[2] = -4.0;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // zero test
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 0.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // pos float test
    a[0] = 0.0;
    a[1] = 7.12345;
    a[2] = 2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = -7.12345;
    cv[1] = 7.12345;
    cv[2] = -0.12345;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos float: passed\n");
    }
    else {
        printf("pos float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg float test
    a[0] = 0.0;
    a[1] = -7.12345;
    a[2] = -2.0;
    
    b[0] = 7.12345;
    b[1] = 0.0;
    b[2] = 2.12345;
    
    cv[0] = -7.12345;
    cv[1] = -7.12345;
    cv[2] = -4.12345;
    
    v3_subtract(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
}
