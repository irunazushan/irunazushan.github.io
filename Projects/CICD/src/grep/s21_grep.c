#include "grep_options.h"

static struct option long_options[] = {
    {"line-number", no_argument, NULL, 'n'},
    {"ignore-case", no_argument, NULL, 'i'},
    {"invert-match", no_argument, NULL, 'v'},
    {"count", no_argument, NULL, 'c'},
    {"files-with-matches", no_argument, NULL, 'l'},
    {"no-filename", no_argument, NULL, 'h'},
    {"no-messages", no_argument, NULL, 's'},
    {"only-matching", no_argument, NULL, 'o'},
    {"regexp", required_argument, NULL, 'e'},
    {"file", required_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}};

int main(int argc, char** argv) {
  int opt, p_q = 0, errors = 0;
  if (argc >= 3) {
    Options flag = init_flags();
    char* token = NULL;
    while ((!errors) && ((opt = getopt_long(argc, argv, "e:f:nivclhso",
                                            long_options, NULL)) != -1)) {
      turn_options(&opt, &flag, &errors, &p_q, token);
    }
    if (!errors) {
      run_grep(argc, argv, &flag, token, &p_q, &errors);
    }
    for (int i = 0; i < p_q; i++) {
      if (flag.patterns[i]) {
        free(flag.patterns[i]);
      }
    }
    if (flag.patterns) {
      free(flag.patterns);
    }
  } else {
    fprintf(stderr, "Usage ./s21_grep [options] template [file_name]\n");
  }
  return 0;
}
