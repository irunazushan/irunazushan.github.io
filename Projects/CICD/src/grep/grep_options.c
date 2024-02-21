#include "grep_options.h"

void turn_options(int* opt, Options* flag, int* errors, int* p_q, char* token) {
  switch (*opt) {
    case 'n':
      flag->n = 1;
      break;
    case 'i':
      flag->i = 1;
      break;
    case 'c':
      flag->c = 1;
      break;
    case 'v':
      flag->v = 1;
      break;
    case 'l':
      flag->l = 1;
      break;
    case 'h':
      flag->h = 1;
      break;
    case 's':
      flag->s = 1;
      break;
    case 'o':
      flag->o = 1;
      break;
    case 'e':
      flag->e = 1;
      token = strtok(optarg, "\\|");
      get_patterns(token, p_q, flag, errors);
      break;
    case 'f':
      get_patterns_from_file(p_q, flag, errors);
      flag->f = 1;
      break;
    default:
      *(errors) = 1;
      fprintf(stderr,
              "usage: s21 grep [-nivclhso] [-e pattern] [-f file] [--null] "
              "[pattern] [file ...]\n");
  }
}

void get_patterns(char* token, int* p_q, Options* flag, int* errors) {
  while (token != NULL) {
    allocate_memory(p_q, flag, errors, token);
    strcpy(flag->patterns[*p_q], token);
    (*p_q)++;
    token = strtok(NULL, "\\|");
  }
}

void allocate_memory(int* p_q, Options* flag, int* errors, char* string) {
  if (*p_q == 0) {
    flag->patterns = (char**)malloc(3 * sizeof(char*));
    *errors = check_memory(flag->patterns);
  } else {
    flag->patterns =
        (char**)realloc(flag->patterns, (4 + *p_q) * sizeof(char*));
    *errors = check_memory(flag->patterns);
  }
  flag->patterns[*p_q] = (char*)malloc(strlen(string) + 1);
  *errors = check_memory(&flag->patterns[*p_q]);
}

int check_memory(char** memory) {
  int memory_error = 0;
  if (memory == NULL) {
    fprintf(stderr, "ERROR: memory is not allocated\n");
    memory_error = 1;
  }
  return memory_error;
}

void get_patterns_from_file(int* p_q, Options* flag, int* errors) {
  FILE* pat_fl;
  pat_fl = fopen(optarg, "r");
  if (pat_fl != NULL) {
    char* pat_line = NULL;
    size_t pat_len = 0;
    ssize_t pat_read;
    while ((int)(pat_read = getline(&pat_line, &pat_len, pat_fl)) != -1) {
      allocate_memory(p_q, flag, errors, pat_line);
      if ((int)strlen(pat_line) == 1) {
        flag->patterns[*p_q][0] = '\n';
        flag->patterns[*p_q][1] = '\0';
      } else {
        for (int i = 0, j = 0; i <= (int)strlen(pat_line); i++, j++) {
          if (pat_line[i] != '\n') {
            flag->patterns[*p_q][j] = pat_line[i];
          } else {
            flag->patterns[*p_q][i] = '\0';
          }
        }
      }
      (*p_q)++;
    }
    if (pat_line) {
      free(pat_line);
    }
    fclose(pat_fl);
  } else {
    fprintf(stderr, "s_21grep: %s: No such file or directory\n", optarg);
    *errors = 1;
  }
}

void apply_options(char* filename, int p_q, Options flag, int amount_of_files) {
  FILE* fl;
  fl = fopen(filename, "r");
  if (fl != NULL) {
    regex_t rx;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter = 1, printed = 0, match = 0, for_l = 0, for_v = 0;
    while ((int)(read = getline(&line, &len, fl)) != -1) {
      for (int x = 0; x < p_q; x++) {
        regcomp(&rx, flag.patterns[x],
                flag.i ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);
        if (flag.v) {
          print_v_line(rx, line, amount_of_files, counter, flag, filename,
                       &for_v, p_q, &match, &for_l);
        } else {
          if (flag.o && !flag.c) {
            print_o(rx, line, amount_of_files, counter, flag, filename, &match,
                    &for_l);
          } else {
            print_line(rx, line, amount_of_files, counter, &printed, flag,
                       filename, &match, &for_l);
          }
        }
        regfree(&rx);
      }
      for_v = 0;
      counter++;
    }
    if (flag.c) {
      print_c(filename, amount_of_files, flag, for_l, match);
    }
    if (flag.l && for_l) {
      printf("%s\n", filename);
    }
    if (line) {
      free(line);
    }
    fclose(fl);
  } else {
    if (!flag.s) {
      fprintf(stderr, "s_21grep: %s: No such file or directory\n", filename);
    }
  }
}

void run_grep(int argc, char** argv, Options* flag, char* token, int* p_q,
              int* errors) {
  if (!flag->e && !flag->f) {
    token = strtok(argv[optind], "\\|");
    get_patterns(token, p_q, flag, errors);
    optind++;
  }
  int amount_of_files = argc - optind;
  for (; optind < argc; optind++) {
    apply_options(argv[optind], *p_q, *flag, amount_of_files);
  }
}

Options init_flags() {
  Options flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
  return flag;
}

void print_line(regex_t rx, char* line, int amount_of_files, int counter,
                int* printed, Options flag, char* filename, int* match,
                int* for_l) {
  if (!(regexec(&rx, line, 0, NULL, 0))) {
    (*for_l) = 1;
    if (counter != *printed) {
      if (!flag.c && !flag.l) {
        prefix(amount_of_files, filename, &flag, counter);
        if (line[strlen(line) - 1] == '\n') {
          printf("%s", line);
        } else {
          printf("%s\n", line);
        }
      }
      (*match)++;
      *printed = counter;
    }
  }
}

void print_o(regex_t rx, char* line, int amount_of_files, int counter,
             Options flag, char* filename, int* match, int* for_l) {
  regmatch_t pat_match;
  if (!(regexec(&rx, line, 1, &pat_match, 0))) {
    (*for_l) = 1;
    char* remained = line;
    if (!flag.c && !flag.l) {
      prefix(amount_of_files, filename, &flag, counter);
      while (!(regexec(&rx, remained, 1, &pat_match, 0))) {
        printf("%.*s\n", (int)(pat_match.rm_eo - pat_match.rm_so),
               remained + pat_match.rm_so);
        remained += pat_match.rm_eo;
      }
      (*match)++;
    }
  }
}

void print_c(char* filename, int amount_of_files, Options flag, int for_l,
             int match) {
  if (amount_of_files > 1 && !(flag.h)) {
    printf("%s:", filename);
  }
  if (flag.l && for_l) {
    printf("1\n");
  } else {
    printf("%d\n", match);
  }
}

void print_v_line(regex_t rx, char* line, int amount_of_files, int counter,
                  Options flag, char* filename, int* for_v, int p_q, int* match,
                  int* for_l) {
  if ((regexec(&rx, line, 0, NULL, 0)) != 0) {
    (*for_v)++;
    if (!flag.c && !flag.l) {
      if (*for_v == p_q) {
        prefix(amount_of_files, filename, &flag, counter);
        if (line[strlen(line) - 1] == '\n') {
          printf("%s", line);
        } else {
          printf("%s\n", line);
        }
      }
    }
    if (*for_v == p_q) {
      (*match)++;
      (*for_l) = 1;
    }
  }
}

void prefix(int amount_of_files, char* filename, Options* flag, int counter) {
  if ((amount_of_files > 1) && (!flag->h)) {
    printf("%s:", filename);
  }
  if (flag->n) {
    printf("%d:", counter);
  }
}
