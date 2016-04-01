#include "args.hpp"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

Args::Args(int argc, char *argv[]) {
  default_values();
  parse(argc, argv);
}

Args::~Args() {
  free(optarg);
  free(query);
}

void Args::default_values() {
  insensitive = false;
  begin_pat = strdup("@id:");
  limit = -1;
  query = nullptr;
  column.push_back("id");
}

void Args::parse(int argc, char *argv[]) {
  char *arg, *pos;
  int opt;
  while((opt = getopt(argc, argv, "b:q:d:iL:r:O:S:")) != -1) {
    switch(opt) {
      case 'b':
        if(begin_pat) {
          free(begin_pat);
        }
        begin_pat = strdup(optarg);
        break;
      case 'q':
        query = strdup(optarg);
        break;
      case 'd':
        pos = strchr(optarg, '.');
        if(pos) {
          pos++;
          tolerance = atoi(pos);
          if(strlen(pos) == 1) {
            tolerance *= 10;
          }
        }
        break;
      case 'i':
        insensitive = true;
        break;
      case 'L':
        limit = atoi(optarg);
        break;
      case 'r':
        break;
      case 'O':
        arg = strdup(optarg);
        column.push_back(strtok(arg, ","));
        while((pos = strtok(NULL, ","))) {
          column.push_back(pos);
        }
        free(arg);
        break;
      case 'S':
        output_size = atoi(optarg);
        break;
    }
  }

  filename = argv[optind];
}
