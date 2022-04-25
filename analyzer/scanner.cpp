#include "scanner.h"

namespace analyzer {

  static const std::string TAG = "Scanner: ";
  Scanner::Scanner() {}
  Scanner::~Scanner() {}

  void Scanner::close() {
    Utils::file_close(this -> loc_stream);
  }

  /* Function for testing for more data in the file. */
  bool Scanner::has_more_data() {
    bool returnValue = true;

    char c = this -> loc_stream.get();

    returnValue = true;
    if (c == EOF) {
      returnValue = false;
    } else {
      this -> loc_stream.putback(c);
    }

    return returnValue;
  }

  /* Function for returning a next token as a string. */
  std::string Scanner::next() {
    bool haveFoundTokenBegin;
    bool haveFoundTokenEnd;
    char c;
    std::string returnValue;
    size_t foundPos = std::string::npos;

    // read a character
    // if EOF, that's an error
    haveFoundTokenBegin = false;
    haveFoundTokenEnd = false;
    c = this -> loc_stream.get();

    if (this -> loc_stream.eof()) {
      Utils::logStream << TAG << "ERROR: no next to read" << std::endl;
      Utils::logStream.flush();
      return "";
    } else {
      // we toss whitespace if we have not found nonwhitespace
      // we append nonwhitespace to the return value

      // read until end of file or until beginning of next token
      while (!this -> loc_stream.eof()) {
        foundPos = Utils::WHITESPACE.find(c);

        if (foundPos == std::string::npos) {
          haveFoundTokenBegin = true;
          if (haveFoundTokenEnd) {
            this -> loc_stream.putback(c);
            break;
          }
          returnValue = returnValue.append(1, c);
        } else {
          // we found whitespace
          // now read until it isn't white space
          if (haveFoundTokenBegin) {
            this -> loc_stream.putback(c); // new line 20130914
            break;
          }
        } 

        c = this -> loc_stream.get();

      } 
    } 

    return returnValue;
  }

  /* Function for returning a next character.*/
  char Scanner::next_char() {
    char c = this -> loc_stream.get();
    return c;
  }

  /* Function for returning the next 'int' value. */
  int Scanner::next_int() {
    int returnValue;
    std::string nextToken;

    nextToken = this -> next();

    returnValue = Utils::str_to_int(nextToken);

    return returnValue;
  }

  /* Function for returning the rest of the line as a string. */
  std::string Scanner::next_line() {
    std::string returnValue;

    getline(this -> loc_stream, returnValue);

    return returnValue;
  }

  /* Function for returning the next 'LONG' value. */
  int64_t Scanner::next_long() {
    int64_t returnValue;
    std::string nextToken;

    nextToken = this -> next();
    returnValue = Utils::str_to_long(nextToken);

    return returnValue;
  }

  /* Function to open a file as a 'Scanner'. */
  void Scanner::open_file(std::string fileName) {
    Utils::file_open(this -> loc_stream, fileName);
  }

  ScanLine::ScanLine() {}

  ScanLine::~ScanLine() {}

  /*  True if there are ANY more characters in the input 'string' */
  bool ScanLine::has_more_data() {
    bool returnValue = true;

    if (scan_line_ss.eof()) {
      returnValue = false;
    }

    return returnValue;
  }

  /* Function 'next' to return the next string. */
  std::string ScanLine::next() {
    std::string token;

    token = "";
    if (!scan_line_ss.eof()) {
      scan_line_ss >> token;
    }

    return token;
  }

  /* return the next LONG. */
  int64_t ScanLine::next_long() {
    int64_t nextValue = 0;
    std::string token = "";

    if (!scan_line_ss.eof()) {
      scan_line_ss >> token;
      nextValue = Utils::str_to_long(token);
    }

    return nextValue;
  }

}