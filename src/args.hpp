#ifndef ARGS_HPP_INCLUDE
#define ARGS_HPP_INCLUDE

#include <string>
#include <vector>

class Args {
public:
  Args(int argc, char *argv[]);
  ~Args();

  char *begin_pat;
  char *query;
  int tolerance;
  bool insensitive;
  int limit;
  std::vector<std::string> column;
  std::string filename;
  int output_size;

private:
  void default_values(void);
  void parse(int args, char *argv[]);
};

#endif /* end of include guard: ARGS_HPP_INCLUDE */

