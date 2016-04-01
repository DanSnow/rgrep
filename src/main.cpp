#include <iostream>

#include "args.hpp"
#include "rgrep.h"

using namespace std;
using namespace RGrep;

int main(int argc, char *argv[]) {
  Args args(argc, argv);
  Query query(args.query, args.insensitive);
  Record record_parser(args.begin_pat, args.filename.c_str());
  int count = 1;
  query.run(record_parser, [&args, &count](Record &record_parser, int rank_value) {
    cout << "rank: " << rank_value << endl;
    for(auto col : args.column) {
      auto attr = record_parser.get_attribute(col.c_str());
      if(attr) {
        cout << col << ": " << attr.value() << endl;
      }
    }
    cout << endl;
    if(~args.limit && count == args.limit) {
      return false;
    }
    ++count;
    return true;
  });
  return 0;
}

/**
 * [v] -b ( begin pattern ) ( 起始位置 )
 * [v] -q (三選一)
 * [v]   single keyword
 * [v]   boolean ( A | B & C )
 * [v]   multitern best match ( AA, BB, +CC, -DD )
 * [ ] -d ( ex：0.2，允許 20％ 的容錯率 )
 * [v] -i ( insensitive 大小寫都可以)
 * [v] -L ( 輸出幾筆 )
 * [ ] -r ( rank )
 * [v] -O ( 想印出的欄位 )
 * [ ] -S ( output size )，可自行微調（優化）
 */
