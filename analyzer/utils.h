#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <string>

namespace analyzer {

  class Utils {
    public:
      static const std::string WHITESPACE;
      static std::ofstream logStream;
      static std::ostringstream oss;

      Utils();
      virtual~Utils();

      static uint8_t letter_loockup(char letter);
      static char num_loockup(uint8_t num);
      static void print_vector(std::vector < char > & characters);

      static void file_open(std::ifstream & inStream);
      static void file_close(std::ifstream & inStream);
      static void file_close(std::ofstream & outStream);
      static void file_open(std::ifstream & inStream,
        const std::string fileName);
      static void file_open(std::ofstream & outStream,
        const std::string fileName);

      static int str_to_int(std::string input);
      static int64_t str_to_long(std::string input);

      static bool has_more_data(std::ifstream & inStream);
  };
}