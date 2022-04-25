#ifndef CRYPTOR_SUBSTITUTION_CIPHER_H_
#define CRYPTOR_SUBSTITUTION_CIPHER_H_

#include "sym_alg.h"
#include <string>
#include <memory>
#include <vector>

namespace cryptor {

  /**
   * Base class for Substitution ciphers
   */
  class SubstitutionCipher: public SymmetricAlgorithm {
    public: virtual~SubstitutionCipher() = default;

    /**
     * Create an instance based on a name
     * @param algo_spec algorithm name
     * @return a null pointer if the algo cannot be found
     */
    static std::unique_ptr < SubstitutionCipher >
    create(const std::string & algo_spec);

    /**
     * Create an instance based on a name
     * @param algo_spec algorithm name
     * Throws a Lookup_Error if the algo/provider combination cannot be found
     */
    static std::unique_ptr < SubstitutionCipher >
    create_or_throw(const std::string & algo_spec);

    /**
     * Encrypt a message
     * @param in the plaintext
     * @param out the byte array to hold the output, i.e. the ciphertext
     * @param len the length of both in and out in bytes
     */
    virtual void encrpyt(const uint8_t in [], uint8_t out[], size_t len) const = 0;

    /**
     * Decrypt a message
     * @param in the plaintext
     * @param out the byte array to hold the output, i.e. the ciphertext
     * @param len the length of both in and out in bytes
     */
    virtual void decrpyt(const uint8_t in [], uint8_t out[], size_t len) const = 0;

    /**
     * @return a new object representing the same algorithm as *this
     */
    SubstitutionCipher * clone() const {
      return this -> new_object().release();
    }

    /**
     * @return new object representing the same algorithm as *this
     */
    virtual std::unique_ptr < SubstitutionCipher > new_object() const = 0;
  };

}

#endif