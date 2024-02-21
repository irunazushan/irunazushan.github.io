#include "cat_options.h"

void apply_options(char* filename, Options flag) {
  FILE* fl;
  fl = fopen(filename, "r");
  if (fl != NULL) {
    int counter = 1;
    int ch;
    int prev_ch = '\n';
    int prev_prev_ch = 0;
    while ((ch = fgetc(fl)) != EOF) {
      if ((flag.s == 1) &&
          ((ch == '\n') && (prev_ch == '\n') && (prev_prev_ch == '\n'))) {
        continue;
      }
      if ((flag.b == 1) && (prev_ch == '\n') && (ch != '\n')) {
        printf("%6d\t", counter);
        counter++;
      }
      if (flag.n == 1 && flag.b == 0 && prev_ch == '\n') {
        printf("%6d\t", counter);
        counter++;
      }
      if (flag.v == 1) {
        if ((ch >= 0 && ch <= 31) && (ch != 9 && ch != 10)) {
          printf("^");
          ch += 64;
        } else if (ch == 127) {
          printf("^");
          ch = 63;  //'?' in ASCII
        } else if (ch >= 128 && ch <= 159) {
          printf("M-^");
          ch -= 64;
        }
      }
      if ((flag.t == 1) && (ch == '\t')) {
        printf("^");
        ch = 73;  //'I' in ASCII
      }
      if ((flag.e == 1) && (ch == '\n')) {
        printf("$");
      }
      printf("%c", ch);
      prev_prev_ch = prev_ch;
      prev_ch = ch;
    }
    fclose(fl);
  } else {
    fprintf(stderr, "s_21cat: %s: No such file or directory\n", filename);
  }
}

int turn_options(int* opt, Options* flag) {
  int correct = 1;
  switch (*opt) {
    case 's':
      flag->s = 1;
      break;
    case 'b':
      flag->b = 1;
      break;
    case 'n':
      flag->n = 1;
      break;
    case 'v':
      flag->v = 1;
      break;
    case 't':
      flag->t = 1;
      flag->v = 1;
      break;
    case 'e':
      flag->e = 1;
      flag->v = 1;
      break;
    case 'E':
      flag->e = 1;
      break;
    case 'T':
      flag->t = 1;
      break;
    default:
      correct = 0;
      fprintf(stderr, "usage: s21_cat [-sbnvteET] [file ...]\n");
  }
  return correct;
}
