#include "vigenere_ciph.h"

namespace cryptor {

  void Vigenere::encrpyt(const uint8_t in [], uint8_t out[], size_t len) const {
    verify_key_set(m_KB.empty() == false);
    for (size_t j = 0; j < len; j++) {
      out[j] = ( in [j] + m_KB[j % m_KB.size()]) % 26;
    }
  }

  void Vigenere::decrpyt(const uint8_t in [], uint8_t out[], size_t len) const {
    verify_key_set(m_KB.empty() == false);
    for (size_t j = 0; j < len; j++) {
      out[j] = ( in [j] - m_KB[j % m_KB.size()] + 26) % 26;
    }
  }

  void Vigenere::key_schedule(const uint8_t key[], size_t key_size) {
    m_KB.resize(key_size);
    copy(key, key + key_size, m_KB.begin());
  }

  void Vigenere::clear() {
    m_KB.clear();
  }

}