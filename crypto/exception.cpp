#include "exception.h"

namespace cryptor {

  std::string to_string(ErrorType type) {
    switch (type) {
    case ErrorType::Unknown:
      return "Unknown";
    case ErrorType::KeyNotSet:
      return "KeyNotSet";
    case ErrorType::LookupError:
      return "LookupError";

    }
    return "Unrecognized  error";
  }

  Exception::Exception(const std::string & msg): m_msg(msg) {}

  Exception::Exception(const std::string & msg,
      const std::exception & e):
    m_msg(msg + " failed with " + std::string(e.what())) {}

  Exception::Exception(const char * prefix,
      const std::string & msg):
    m_msg(std::string(prefix) + " " + msg) {}

  Lookup_Error::Lookup_Error(const std::string & type,
      const std::string & algo):
    Exception("Unavailable " + type + " " + algo) {}

  Key_Not_Set::Key_Not_Set(const std::string & algo):
    Invalid_State("Key not set in " + algo) {}

}