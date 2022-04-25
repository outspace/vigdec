#include "utils.h"
#include <iomanip>

namespace analyzer {

  static const std::string TAG = "Utils: ";
  const std::string Utils::WHITESPACE = " \n\t\r";

  std::ofstream Utils::logStream;
  std::ostringstream Utils::oss;

  Utils::Utils() {}

  Utils::~Utils() {}

  /* Close an input stream. */
  void Utils::file_open(std::ifstream & inStream) {
    inStream.close();
  }

  /* Close an input stream. */
  void Utils::file_close(std::ifstream & inStream) {
    inStream.close();
  }

  /* Close an output stream. */
  void Utils::file_close(std::ofstream & outStream) {
    outStream.close();
  }

  /* Open an input stream. */
  void Utils::file_open(std::ifstream & inStream, std::string fileName) {
    inStream.open(fileName.c_str());
    if (inStream.fail()) {
      std::cout << TAG << "open failed for " << fileName << std::endl;
      exit(0);
    }
  }

  /* Open an output stream. */
  void Utils::file_open(std::ofstream & outStream, std::string fileName) {
    outStream.open(fileName.c_str());
    if (outStream.fail()) {
      std::cout << TAG << "open failed for " << fileName << std::endl;
      exit(0);
    }
  }

  /* Returns letter alphabet nubmer by the letter. */
  uint8_t Utils::letter_loockup(char letter) {
    if (letter >= 'A' && letter <= 'Z')
      return letter - 'A';
    if (letter >= 'a' && letter <= 'z')
      return letter - 'a';
    return 100;
  }

  /* Returns letter by the alphabet number. */
  char Utils::num_loockup(uint8_t num) {
    if (num < 26) {
      return num + 'A';
    }
    return '@';
  }

  /* Prints vector of char to stdout. */
  void Utils::print_vector(std::vector < char > & characters) {
    for (int i = 0; i < characters.size(); i++) {
      std::cout << characters[i];
    }
    std::cout << std::endl;
  }

  /* Convert a string to an integer. */
  int Utils::str_to_int(std::string input) {
    bool isNegative;
    int returnValue = 0;
    const std::string digits = "0123456789";

    isNegative = false;
    if ("-" == input.substr(0, 1)) {
      isNegative = true;
      input = input.substr(1);
    }

    for (std::string::iterator iter = input.begin(); iter != input.end(); ++iter) {
      int digit = digits.find( * iter);
      if ((0 > digit) || (9 < digit)) {
        Utils::logStream << TAG << "ERROR: string '" << input <<
          "' not a number" << std::endl;
        Utils::logStream.flush();
        exit(0);
      }
      returnValue = 10 * returnValue + digit;
    }

    if (isNegative) returnValue = -returnValue;

    return returnValue;
  }

  /* Convert a string to a Long. */
  int64_t Utils::str_to_long(std::string input) {
    int64_t returnValue = 0;
    const std::string digits = "0123456789";

    for (std::string::iterator iter = input.begin(); iter != input.end(); ++iter) {
      int digit = digits.find( * iter);
      if ((0 > digit) || (9 < digit)) {
        Utils::logStream << TAG << "ERROR: string '" << input <<
          "' not a number" << std::endl;
        Utils::logStream.flush();
        exit(0);
      }
      returnValue = 10 * returnValue + digit;
    }

    return returnValue;
  }

}