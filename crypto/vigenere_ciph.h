#include "subst_cipher.h"

#include <vector>


namespace cryptor {

  /**
   * Vigenere cipher
   */
  class Vigenere final: public SubstitutionCipher {
    public: 
      void encrpyt(const uint8_t in [], uint8_t out[], size_t len) const override;
      void decrpyt(const uint8_t in [], uint8_t out[], size_t len) const override;
      void set_iv(const uint8_t iv[], size_t iv_len) {};
      void clear() override;
      std::string name() const override {
        return "Vigenere";
      }
      std::unique_ptr < SubstitutionCipher > new_object() const override {
        return std::make_unique < Vigenere > ();
      }

    private: 
      void key_schedule(const uint8_t[], size_t) override;
      std::vector < uint8_t > m_KB;
  };

}