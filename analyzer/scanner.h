#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "utils.h"

namespace analyzer {

  class Scanner {
    public:
      Scanner();
      virtual~Scanner();

      std::ifstream loc_stream;

      void close();
      bool has_more_data();
      char next_char();
      std::string next();
      std::string next_line();
      void open_file(std::string fileName);
      int next_int();
      int64_t next_long();
  };

  class ScanLine {
    public:
      std::stringstream scan_line_ss;

      ScanLine();
      virtual~ScanLine();

      bool has_more_data();
      void open_string(std::string line);
      std::string next();
      int next_int();
      int64_t next_long();
      std::string next_line();
  };

}