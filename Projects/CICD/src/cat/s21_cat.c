#include "cat_options.h"

static struct option long_options[] = {
    {"squeeze-blank", no_argument, NULL, 's'},
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {NULL, 0, NULL, 0}};

int main(int argc, char** argv) {
  Options flag = {0, 0, 0, 0, 0, 0};
  int opt, is_correct = 1;
  while ((opt = getopt_long(argc, argv, "+sbnvteET", long_options, NULL)) !=
         -1) {
    is_correct = turn_options(&opt, &flag);
  }
  if (is_correct) {
    for (; optind < argc; optind++) {
      apply_options(argv[optind], flag);
    }
  }
  return 0;
}
