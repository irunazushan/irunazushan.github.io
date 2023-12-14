#ifndef CAT_OPTIONS_H
#define CAT_OPTIONS_H

#include <getopt.h>
#include <stdio.h>
#include <string.h>

struct Options_s {
  int s;
  int v;
  int n;
  int b;
  int t;
  int e;
};

typedef struct Options_s Options;

void apply_options(char* filename, Options flag);
int turn_options(int* opt, Options* flag);

#endif
