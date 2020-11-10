#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//input functions
void num(char *inppath, double *x);
void array(char *inppath, double *x, size_t xsize);

//transforming functions
void add(double *x, size_t xsize, double b);
void sub(double *x, size_t xsize, double b);
void mult(double *x, size_t xsize, double b);
void power(double *x, size_t xsize, double b);
void med(double *x, size_t *xsize);
void mean(double *x, size_t *xsize);
void max(double *x, size_t *xsize);
void min(double *x, size_t *xsize);
void extract(char *outpath, double *x, size_t xsize);
void sort(double *x, size_t xsize);
void idx(double *x, size_t *xsize, size_t d);

#endif