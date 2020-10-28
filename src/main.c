#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/lex.h"
#include "../inc/utils.h"


int tk;
char str[MAXLEN];


int main(int argc, char * argv[]) {

  //passing destination path correctly
  if( argc > 3 ) {
    printf("Error: Too many arguments.\nTry again with:\n\t%s <input-file-path> <model-file-path>\n", argv[0]);
    exit(1);
  }
  else if( argc < 3 ) {
    printf("Error: Model file path expected.\nTry again with:\n\t%s <input-file-path> <model-file-path>\n", argv[0]);
    exit(1);
  }

  double *x;  //passing argument
  size_t xsize;
  double *input;  //input register
  size_t inputsize;
  int state = 0;  //model state
  int layerNum = 0;  //model layerNum
  double d;

	//open model file
	mfile = fopen(argv[2], "r");
	if(mfile == NULL){
		printf("Error: Model file missing or corrupted.\nTry using a different path.\n");
		exit(1);
	}

  //start model builder
  printf("\n> model: ");
  tk=lex(str);
  if(tk == 10) {
    printf("-");
    state = 2;
  }
  else {
    printf("\n\nError: Starting dash (-) missing.\n");
    state = 4;
  }
  while(1){
    tk=lex(str);
    //state 0: expecting dash(-)
    if(state == 0) {
      if(tk == 10){
        printf("-");
        state = 1;
      }
      else{
        printf("\n\nError: Dash (-) expected\n");
        state = 4;
      }
    }
    //state 1: expecting a function
    else if(state == 1) {
      if(tk == 22){
        printf("add");

        tk=lex(str);
        if(tk == 12){
          printf("(int%s)", str);
        }
        else if(tk == 13) {
          printf("(real%s)", str);
        }
        else {
          printf("\n\nError: Numeral value expected.\n");
          state = 4;
          continue;
        }
        sscanf(str, "%lf", &d);
        add(x, xsize, d);

        state = 0;
        layerNum++;
      }
      else if(tk == 23) {
        printf("sub");

        tk=lex(str);
        if(tk == 12) {
          printf("(int%s)", str);
        }
        else if(tk == 13) {
          printf("(real%s)", str);
        }
        else {
          printf("\n\nError: Numeral value expected.\n");
          state = 4;
          continue;
        }
        sscanf(str, "%lf", &d);
        sub(x, xsize, d);

        state = 0;
        layerNum++;
      }
      else if(tk == 24) {
        printf("mult");

        tk=lex(str);
        if(tk == 12) {
          printf("(int%s)", str);
        }
        else if(tk == 13) {
          printf("(real%s)", str);
        }
        else {
          state = 4;
          printf("\n\nError: Numeral value expected.\n");
          continue;
        }
        sscanf(str, "%lf", &d);
        mult(x, xsize, d);

        state = 0;
        layerNum++;
      }
      else if(tk == 25) {
        printf("pow");

        tk=lex(str);
        if(tk == 12) {
          printf("(int%s)", str);
        }
        else if(tk == 13) {
          printf("(real%s)", str);
        }
        else {
          printf("\n\nError: Numeral value expected.\n");
          state = 4;
          continue;
        }
        sscanf(str, "%lf", &d);
        power(x, xsize, d);

        state = 0;
        layerNum++;
      }
      else if(tk == 26) {
        printf("med");
        med(x, &xsize);
        x = (double*) realloc(x, 1);
        state = 0;
        layerNum++;
      }
      else if(tk == 27) {
        printf("mean");
        mean(x, &xsize);
        x = (double*) realloc(x, 1);
        state = 0;
        layerNum++;
      }
      else if(tk == 28) {
        printf("max");
        state = 0;
        layerNum++;
      }
      else if(tk == 29) {
        printf("min");
        state = 0;
        layerNum++;
      }
      else if(tk == 30) {
        printf("( o )");
        state = 0;
        layerNum++;
      }
      else if(tk == 31) {
        printf("extract");
        state = 0;
        layerNum++;
      }
      //EOF
      else if(tk == 15) {
        state = 3;
      }
      else {
        printf("\n\nError: Function expected.\n");
        state = 4;
      }
    }
    //state 2: expecting an input function
    else if(state == 2) {
      if(tk == 20) {
        printf("num");
        xsize=1;
        inputsize=1;
        x = (double*) malloc(sizeof(double));
        input = (double*) malloc(sizeof(double));
        num(argv[1], x);
        *input = *x;

        state = 0;
        layerNum++;
      }
      else if(tk == 21) {

        printf("array");

        //array size
        tk=lex(str);
        if(tk == 12) {
          printf("%s", str);
          xsize=(size_t)atoi(str);
          inputsize=xsize;
        }
        else {
          printf("\n\nError: Array size expected.\n");
          state = 4;
          continue;
        }
        // import array
        x = (double*) malloc(xsize*sizeof(double));
        input = (double*) malloc(xsize*sizeof(double));
        array(argv[1], x, xsize);
        for(int i=0; i<xsize; i++) {
          *(input+i)=*(x+i);
        }

        state = 0;
        layerNum++;
      }
      else {
        printf("\n\nError: Input function expected.\n");
        state = 4;
      }
    }
    //state 3: final state (success)
    else if(state == 3) {
      printf("\n\nModel was built successfully.\n");

      //print depth
      if(layerNum != 1) printf(" . depth: %d layers\n", layerNum);
      else printf(" . depth: 1 layer\n");

      //print input
      if(inputsize != 1) {
        printf(" . input: [ %g", *input);
        for (size_t i=1; i<inputsize; i++) printf(", %g", *(input+i));
        printf(" ]\n");
      }
      else {
        printf(" . input: %g\n", *input);
      }

      //print output
      if(xsize != 1) {
        printf(" . output: [ %g", *x);
        for (size_t i=1; i<xsize; i++) printf(", %g", *(x+i));
        printf(" ]\n");
      }
      else {
        printf(" . output: %g\n", *x);
      }

      free(x);
      free(input);
      break;
    }
    //state 4: final state (fail)
    else if(state == 4) {
      printf("Failure: Abort reading.\n");
      break;
    }
  }

  // edo tha kano ta magika
	fclose(mfile);
	return 0;
}
