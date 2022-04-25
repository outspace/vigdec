#include "subst_cipher.h"
#include "exception.h"
#include "vigenere_ciph.h"

namespace cryptor {

  std::unique_ptr < SubstitutionCipher > 
    SubstitutionCipher::create(const std::string & algo_spec) {
    if (algo_spec == "Vigenere") {
      return std::make_unique < Vigenere > ();
    }

    return nullptr;
  }

  std::unique_ptr < SubstitutionCipher >
    SubstitutionCipher::create_or_throw(const std::string & algo) {
      if (auto sc = SubstitutionCipher::create(algo)) {
        return sc;
      }
      throw Lookup_Error("Substitution cipher", algo);
    }

}