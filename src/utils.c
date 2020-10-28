#include "../inc/utils.h"

void swap(double *p,double *q) {
   double t;

   t=*p;
   *p=*q;
   *q=t;
}

void sort(double *x, size_t xsize) {
   int i,j;

   for(i = 0;i < xsize-1;i++) {
      for(j = 0;j < xsize-i-1;j++) {
         if(x[j] > x[j+1])
            swap(&x[j],&x[j+1]);
      }
   }
}

void num(char *argv1, double *x) {

  FILE *ifile = fopen(argv1, "r");
  if(ifile == NULL){
    printf("\n\nError: Input file missing or corrupted.\nTry using a different path..\n");
    exit(0);
  }

  fscanf(ifile,"%lf", x);
  fclose(ifile);
}

void array(char *argv1, double *x, size_t xsize) {

  FILE *ifile = fopen(argv1, "r");
  double *num = (double*) malloc(sizeof(double));

  if(ifile == NULL){
    printf("\n\nError: Input file missing or corrupted.\nTry using a different path..\n");
    exit(0);
  }

  for(size_t i=0; i<xsize; i++) {
    fscanf(ifile,"%lf", num);
    *(x+i)=*num;
  }

  free(num);
  fclose(ifile);
}

void add(double *x, size_t xsize, double b) {
  for(size_t i=0; i<xsize; i++) {
    *(x+i) = *(x+i) + b;
  }
}

void sub(double *x, size_t xsize, double b) {
  for(size_t i=0; i<xsize; i++) {
    *(x+i) = *(x+i) - b;
  }
}

void mult(double *x, size_t xsize, double b) {
  for(size_t i=0; i<xsize; i++) {
    *(x+i) = *(x+i) * b;
  }
}

void power(double *x, size_t xsize, double b) {
  for(size_t i=0; i<xsize; i++) {
    *(x+i) = pow(*(x+i), b);
  }
}

void mean(double *x, size_t *xsize) {
  double t;
  for(size_t i=0; i<*xsize; i++){
    t += *(x+i);
  }
  t = t / *xsize;
  *x = t;
  *xsize = 1;
}

void med(double *x, size_t *xsize) {
  double t;
  size_t n = (*xsize+1)/2-1;
  sort(x, *xsize);

  t = *(x+n);
  *x = t;
  *xsize = 1;
}
