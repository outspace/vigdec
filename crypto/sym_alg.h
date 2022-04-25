#include <cstdint>
#include <string>
#include <vector>

namespace cryptor {

  /**
   * This class for a symmetric algorithm object.
   */
  class SymmetricAlgorithm {
    public:
      virtual~SymmetricAlgorithm() =
      default;

    /**
     * Reset the state.
     */
    virtual void clear() = 0;

    template < typename Alloc >
      void set_key(const std::vector < uint8_t, Alloc > & key) {
        set_key(key.data(), key.size());
      }

    /**
     * Set the symmetric key of this object.
     * @param key the to be set as a byte array.
     * @param length in bytes of key param
     */
    void set_key(const uint8_t key[], size_t length);

    /**
     * @return the algorithm name
     */
    virtual std::string name() const = 0;

    protected:
      void verify_key_set(bool cond) const {
        if (cond == false)
          throw_key_not_set_error();
      }

    private:
      void throw_key_not_set_error() const;

    /**
     * Run the key schedule
     */
    virtual void key_schedule(const uint8_t key[], size_t length) = 0;
  };

}