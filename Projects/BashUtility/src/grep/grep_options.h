#ifndef GREP_OPTIONS_H
#define GREP_OPTIONS_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Options_s {
  int n;
  int i;
  int v;
  int c;
  int l;
  int h;
  int s;
  int o;
  int e;
  int f;
  char** patterns;
};
typedef struct Options_s Options;

void turn_options(int* opt, Options* flag, int* errors, int* p_q, char* token);
void apply_options(char* filename, int p_q, Options flag, int amount_of_files);
void print_line(regex_t rx, char* line, int amount_of_files, int counter,
                int* printed, Options flag, char* filename, int* match,
                int* for_l);
void print_v_line(regex_t rx, char* line, int amount_of_files, int counter,
                  Options flag, char* filename, int* for_v, int p_q, int* match,
                  int* for_l);
void allocate_memory(int* p_q, Options* flag, int* errors, char* string);
int check_memory(char** memory);
void get_patterns(char* token, int* p_q, Options* flag, int* errors);
void get_patterns_from_file(int* p_q, Options* flag, int* errors);
void print_o(regex_t rx, char* line, int amount_of_files, int counter,
             Options flag, char* filename, int* match, int* for_l);
void print_c(char* filename, int amount_of_files, Options flag, int for_l,
             int match);
void prefix(int amount_of_files, char* filename, Options* flag, int counter);
Options init_flags();
void run_grep(int argc, char** argv, Options* flag, char* token, int* p_q,
              int* errors);

#endif
