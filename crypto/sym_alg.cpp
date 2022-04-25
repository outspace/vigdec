#include "sym_alg.h"
#include "exception.h"

namespace cryptor {

  void SymmetricAlgorithm::throw_key_not_set_error() const {
    throw Key_Not_Set(name());
  }

  void SymmetricAlgorithm::set_key(const uint8_t key[], size_t length) {
    key_schedule(key, length);
  }

}