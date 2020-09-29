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
void test_scale(float *dst);
void test_angle(float *dst, float *a, float *b); // angle between a and b
void test_angle_quick(float *dst, float *a, float *b); // angle between a and b; no cos-1
void test_reflect(float *dst, float *v, float *n);
void test_length(float *a);
void test_normalize(float *dst, float *a);

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
    test_cross_product(testVectDest, testVectA, testVectB);
    
    printf("\ntest scale:\n");
    test_scale(testVectDest);
    
    printf("\ntest angle:\n");
    test_angle(testVectDest, testVectA, testVectB);
    
    printf("\ntest angle quick:\n");
    test_angle_quick(testVectDest, testVectA, testVectB);
    
    printf("\ntest reflect:\n");
    test_reflect(testVectDest, testVectA, testVectB);
    
    printf("\ntest length\n");
    test_length(testVectA);
    
    printf("\ntest normalize\n");
    test_normalize(testVectDest,testVectA);
    return 0;
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
    
    cv[0] = 14.0;
    cv[1] = 14.0;
    cv[2] = -49.0;
    
    v3_cross_product(dst, a, b);
    
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
    
    cv[0] = -14.0;
    cv[1] = -14.0;
    cv[2] = 49.0;
    
    v3_cross_product(dst, a, b);
    
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
    
    v3_cross_product(dst, a, b);
    
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
    
    cv[0] = 15.12628;
    cv[1] = 14.2469;
    cv[2] = -50.74353;
    
    v3_cross_product(dst, a, b);
    
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
    
    cv[0] = -15.12628;
    cv[1] = -14.2469;
    cv[2] = 50.74353;
    
    v3_cross_product(dst, a, b);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
}

void test_scale(float *dst){
    float cv[3];
    float s;
    
    // pos int test
    s = 2;
    
    dst[0] = 0.0;
    dst[1] = 7.0;
    dst[2] = -2.0;
    
    cv[0] = 0.0;
    cv[1] = 14.0;
    cv[2] = -4.0;
    
    v3_scale(dst, s);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg int test
    s = -2;
    
    dst[0] = 0.0;
    dst[1] = 7.0;
    dst[2] = -2.0;
    
    cv[0] = 0.0;
    cv[1] = -14.0;
    cv[2] = 4.0;
    
    v3_scale(dst, s);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // zero test
    s = 0;
    
    dst[0] = 0.0;
    dst[1] = 7.0;
    dst[2] = -2.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    
    v3_scale(dst, s);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // pos float test
    s = 2.12345;
    
    dst[0] = 0.0;
    dst[1] = 7.0;
    dst[2] = -2.0;
    
    cv[0] = 0.0;
    cv[1] = 14.86415;
    cv[2] = -4.2469;
    
    v3_scale(dst, s);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos floats: passed\n");
    }
    else {
        printf("pos floats: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg float test
    s = -2.12345;
    
    dst[0] = 0.0;
    dst[1] = 7.0;
    dst[2] = -2.0;
    
    cv[0] = 0.0;
    cv[1] = -14.86415;
    cv[2] = 4.2469;
    
    v3_scale(dst, s);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg floats: passed\n");
    }
    else {
        printf("neg floats: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
}

void test_angle(float *dst, float *a, float *b) {
    float val;
    float cval;
    
    // 2 pos
    a[0] = 1.0;
    a[1] = 2.12345;
    a[2] = 3.0;
    
    b[0] = 2.54321;
    b[1] = 1.0;
    b[2] = 3.12345;
    
    val = v3_angle(a, b);
    cval = 0.4779207;
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("2 pos: passed\n");
    }
    else {
        printf("2 pos: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    }
    
    // 2 neg
    a[0] = -1.0;
    a[1] = -2.12345;
    a[2] = -3.0;
    
    b[0] = -2.54321;
    b[1] = -1.0;
    b[2] = -3.12345;
    
    val = v3_angle(a, b);
    cval = 0.4779207;
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("2 neg: passed\n");
    }
    else {
        printf("2 neg: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    }
    
    // 1 each
    a[0] = 1.0;
    a[1] = 2.12345;
    a[2] = 3.0;
    
    b[0] = -2.54321;
    b[1] = -1.0;
    b[2] = -3.12345;
    
    val = v3_angle(a, b);
    cval = 2.6636719;
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("1 pos 1 neg: passed\n");
    }
    else {
        printf("1 pos 1 neg: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    }
    
    // equal
    a[0] = 1.0;
    a[1] = 2.12345;
    a[2] = 3.0;
    
    b[0] = 1.0;
    b[1] = 2.12345;
    b[2] = 3.0;
    
    val = v3_angle(a, b);
    cval = 0.0;
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("same angle: passed\n");
    }
    else {
        printf("same angle: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    } 
}

void test_angle_quick(float *dst, float *a, float *b) {
    float val;
    float cval;
    
    // 2 pos
    a[0] = 1.0;
    a[1] = 2.12345;
    a[2] = 3.0;
    
    b[0] = 2.54321;
    b[1] = 1.0;
    b[2] = 3.12345;
    
    val = v3_angle_quick(a, b);
    cval = cos(0.4779207);
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("2 pos: passed\n");
    }
    else {
        printf("2 pos: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    }
    
    // 2 neg
    a[0] = -1.0;
    a[1] = -2.12345;
    a[2] = -3.0;
    
    b[0] = -2.54321;
    b[1] = -1.0;
    b[2] = -3.12345;
    
    val = v3_angle_quick(a, b);
    cval = cos(0.4779207);
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("2 neg: passed\n");
    }
    else {
        printf("2 neg: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    }
    
    // 1 each
    a[0] = 1.0;
    a[1] = 2.12345;
    a[2] = 3.0;
    
    b[0] = -2.54321;
    b[1] = -1.0;
    b[2] = -3.12345;
    
    val = v3_angle_quick(a, b);
    cval = cos(2.6636719);
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("1 pos 1 neg: passed\n");
    }
    else {
        printf("1 pos 1 neg: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    }
    
    // equal
    a[0] = 1.0;
    a[1] = 2.12345;
    a[2] = 3.0;
    
    b[0] = 1.0;
    b[1] = 2.12345;
    b[2] = 3.0;
    
    val = v3_angle_quick(a, b);
    cval = cos(0.0);
    
    if(v3_val_equals(val, cval, .0001)) {
        printf("same angle: passed\n");
    }
    else {
        printf("same angle: failed\n");
        printf("\texpected: %.6f\n", cval);
        printf("\tactual: %.6f\n", val);
    } 
}

void test_reflect(float *dst, float *v, float *n) {
    float cv[3];
    
    // pos int test
    v[0] = -2.0;
    v[1] = 2.0;
    v[2] = 0.0;
    
    n[0] = 0.0;
    n[1] = 1.0;
    n[2] = 0.0;
    
    cv[0] = -2.0;
    cv[1] = -2.0;
    cv[2] = 0;
    
    v3_reflect(dst, v, n);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos ints: passed\n");
    }
    else {
        printf("pos ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg int test
    v[0] = 0.0;
    v[1] = -7.0;
    v[2] = -2.0;
    
    n[0] = 7.0;
    n[1] = 0.0;
    n[2] = 2.0;
    
    cv[0] = 7.692192;
    cv[1] = -7.0;
    cv[2] = 0.197769;
    
    v3_reflect(dst, v, n);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg ints: passed\n");
    }
    else {
        printf("neg ints: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // zero test
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
    
    n[0] = 0.0;
    n[1] = 0.0;
    n[2] = 0.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    
    v3_reflect(dst, v, n);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // pos float test
    v[0] = 0.0;
    v[1] = 7.12345;
    v[2] = 2.0;
    
    n[0] = 7.12345;
    n[1] = 0.0;
    n[2] = 2.12345;
    
    cv[0] = -8.139845;
    cv[1] = 7.123450;
    cv[2] = -0.426430;
    
    v3_reflect(dst, v, n);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("pos float: passed\n");
    }
    else {
        printf("pos float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
    
    // neg float test
    v[0] = 0.0;
    v[1] = -7.12345;
    v[2] = -2.0;
    
    n[0] = 7.12345;
    n[1] = 0.0;
    n[2] = 2.12345;
    
    cv[0] = 8.139845;
    cv[1] = -7.123450;
    cv[2] = 0.426430;
    
    v3_reflect(dst, v,n);
    
    if(v3_equals(dst, cv, 0.0001)) {
        printf("neg float: passed\n");
    }
    else {
        printf("neg float: failed\n");
        printf("\texpected: [%.6f, %.6f, %.6f]\n", cv[0], cv[1], cv[2]);
        printf("\tactual: [%.6f, %.6f, %.6f]\n", dst[0], dst[1], dst[2]);
    }
}

void test_normalize(float *dst,float *a) {
    float val;
    float cv[3];
    // all pos
    a[0] = 1.3;
    a[1] = 2.2;
    a[2] = 3.1;
    
    cv[0] = 0.30103;
    cv[1] = 0.55190;
    cv[2] = 0.77767;
    v3_normalize(dst,a);
    if(v3_equals(dst, cv, .0001)) {
        printf("all pos: passed\n");
    }
    else {
        printf("all pos: failed\n");
        printf("\texpected: %.6f\n", dst);
        printf("\tactual: %.6f\n", val);
    }
    
    // 1 neg
    a[0] = 1.3;
    a[1] = -2.2;
    a[2] = 3.1;
    
    cv[0] = 0.32358;
    cv[1] = -0.54760;
    cv[2] = 0.77163;
    v3_normalize(dst,a);
    if(v3_equals(dst, cv, .0001)) {
        printf("1 neg: passed\n");
    }
    else {
        printf("1 neg: failed\n");
        printf("\texpected: %.6f\n", dst);
        printf("\tactual: %.6f\n", val);
    }
    
    // 2 neg
    a[0] = 1.3;
    a[1] = -2.2;
    a[2] = -3.1;
    
    cv[0] = 0.32358;
    cv[1] = -0.54760;
    cv[2] = -0.77163;
    v3_normalize(dst,a);
    if(v3_equals(dst, cv, .0001)) {
        printf("2 neg: passed\n");
    }
    else {
        printf("2 neg: failed\n");
        printf("\texpected: %.6f\n", dst);
        printf("\tactual: %.6f\n", val);
    }
    
    // all neg
    a[0] = -1.3;
    a[1] = -2.2;
    a[2] = -3.1;
    
    cv[0] = -0.32358;
    cv[1] = -0.54760;
    cv[2] = -0.77163;
    v3_normalize(dst,a);
    if(v3_equals(dst, cv, .0001)) {
        printf("all neg: passed\n");
    }
    else {
        printf("all neg: failed\n");
        printf("\texpected: %.6f\n", dst);
        printf("\tactual: %.6f\n", val);
    }
    
    // zero
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    cv[0] = 0.0;
    cv[1] = 0.0;
    cv[2] = 0.0;
    v3_normalize(dst,a);
    if(v3_equals(dst, cv, .0001)) {
        printf("all zero: passed\n");
    }
    else {
        printf("all zero: failed\n");
        printf("\texpected: %.6f\n", dst);
        printf("\tactual: %.6f\n", val);
    }
}

void test_length(float *a) {
    float val;
    float l;
    // all pos
    a[0] = 1.3;
    a[1] = 2.2;
    a[2] = 3.1;
    
    l = 4.0174618;
    val = v3_length(a);
    if(v3_val_equals(val, l, .0001)) {
        printf("all pos: passed\n");
    }
    else {
        printf("all pos: failed\n");
        printf("\texpected: %.6f\n", l);
        printf("\tactual: %.6f\n", val);
    }
    
    // 1 neg
    a[0] = 1.3;
    a[1] = -2.2;
    a[2] = 3.1;
    
    l = 4.0174618;
    val = v3_length(a);
    if(v3_val_equals(val, l, .0001)) {
        printf("1 neg: passed\n");
    }
    else {
        printf("1 neg: failed\n");
        printf("\texpected: %.6f\n", l);
        printf("\tactual: %.6f\n", val);
    }
    
    // 2 neg
    a[0] = 1.3;
    a[1] = -2.2;
    a[2] = -3.1;
    
    l = 4.0174618;
    val = v3_length(a);
    if(v3_val_equals(val, l, .0001)) {
        printf("2 neg: passed\n");
    }
    else {
        printf("2 neg: failed\n");
        printf("\texpected: %.6f\n", l);
        printf("\tactual: %.6f\n", val);
    }
    
    // all neg
    a[0] = -1.3;
    a[1] = -2.2;
    a[2] = -3.1;
    
    l = 4.0174618;
    val = v3_length(a);
    if(v3_val_equals(val, l, .0001)) {
        printf("all neg: passed\n");
    }
    else {
        printf("all neg: failed\n");
        printf("\texpected: %.6f\n", l);
        printf("\tactual: %.6f\n", val);
    }
    
    // zero
    a[0] = 0.0;
    a[1] = 0.0;
    a[2] = 0.0;
    
    l = 0.0;
    val = v3_length(a);
    if(v3_val_equals(val, l, .0001)) {
        printf("zero: passed\n");
    }
    else {
        printf("zero: failed\n");
        printf("\texpected: %.6f\n", l);
        printf("\tactual: %.6f\n", val);
    }
}