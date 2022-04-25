#ifndef CRYPTOR_EXCEPTION_H_
#define CRYPTOR_EXCEPTION_H_

#include <exception>

#include <string>

namespace cryptor {

  /**
   * Different types of errors that might occur
   */
  enum class ErrorType {
      /** Some unknown error */
      Unknown = 1,
      /** Invalid object state */
      InvalidObjectState = 10,
      /** A key was not set on an object when this is required */
      KeyNotSet,
      /** An object type was requested but cannot be found */
      LookupError,

  };

  //! \brief Convert an ErrorType to string
  std::string to_string(ErrorType type);

  /**
   * Base class for all exceptions thrown by the library
   */
  class Exception: public std::exception {
    public:
      /**
       * Return a descriptive string which is hopefully comprehensible to
       * a developer. It will likely not be useful for an end user.

       */
      const char * what() const noexcept override {
        return m_msg.c_str();
      }

    /**
     * Return the "type" of error which occurred.
     */
    virtual ErrorType error_type() const noexcept {
      return cryptor::ErrorType::Unknown;
    }

    /**
     * Return an error code associated with this exception, or otherwise 0.
     *
     * The domain of this error varies depending on the source, for example on
     * POSIX systems it might be errno, while on a Windows system it might be
     * the result of GetLastError or WSAGetLastError.
     */
    virtual int error_code() const noexcept {
      return 0;
    }

    /**
     * Avoid throwing base Exception, use a subclass
     */
    explicit Exception(const std::string & msg);

    /**
     * Avoid throwing base Exception, use a subclass
     */
    Exception(const char * prefix,
      const std::string & msg);

    /**
     * Avoid throwing base Exception, use a subclass
     */
    Exception(const std::string & msg,
      const std::exception & e);

    private: std::string m_msg;
  };

  /**
   * Invalid state was encountered. A request was made on an object while the
   * object was in a state where the operation cannot be performed.
   */
  class Invalid_State: public Exception {
    public: explicit Invalid_State(const std::string & err): Exception(err) {}

    ErrorType error_type() const noexcept override {
      return ErrorType::InvalidObjectState;
    }
  };

  
 /**
  * A request was made for some kind of object which could not be located
  */
  class Lookup_Error : public Exception
   {
   public:
      explicit Lookup_Error(const std::string& err) : Exception(err) {}

      Lookup_Error(const std::string& type,
                   const std::string& algo);

      ErrorType error_type() const noexcept override { return ErrorType::LookupError; }
   };

  /**
   * The key was not set on an object. This occurs with symmetric objects where
   * an operation which requires the key is called prior to set_key being called.
   */
  class Key_Not_Set: public Invalid_State {
    public: explicit Key_Not_Set(const std::string & algo);

    ErrorType error_type() const noexcept override {
      return ErrorType::KeyNotSet;
    }
  };

  template < typename E, typename...Args >
    inline void do_throw_error(const char * file, int line,
      const char * func, Args...args) {
      throw E(file, line, func, args...);
    }

}

#endif