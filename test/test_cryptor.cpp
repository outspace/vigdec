#include "include/gtest/gtest.h"
#include "../crypto/subst_cipher.h"
#include "../crypto/exception.h"
#include "../analyzer/utils.h"
#include <string>

/* Some tests for cipher instance creation */
TEST(Cryptor_Common, Create)
{
   auto cipher = cryptor::SubstitutionCipher::create("NoExistCipher");
   EXPECT_EQ(cipher, nullptr) 
            << "Cipher creator must return nullptr for no exist cipher";
   cipher = cryptor::SubstitutionCipher::create("Vigenere");
   EXPECT_TRUE(cipher != nullptr) 
            << "Cipher creator must return cipher instanse for exist cipher";
   EXPECT_THROW(cryptor::SubstitutionCipher::create_or_throw("NoExistCipher"), std::exception)
            << "Cipher cretor must throw exeption for non exist cipher";
   EXPECT_NO_THROW(cryptor::SubstitutionCipher::create_or_throw("Vigenere"))
            << "Cipher cretor must not throw exeption for exist cipher";
}

/* Some tests for Vigenere cipher key setup */
TEST(Cryptor_Vigenere, SetKey)
{
    std::vector<uint8_t> in({1,2,3,4});
    std::vector<uint8_t> out(4);
    std::vector<uint8_t> key({4,3,2,1});
    auto cipher = cryptor::SubstitutionCipher::create("Vigenere");
    EXPECT_THROW(cipher->encrpyt(&in[0], &out[0], in.size()), std::exception)
            << "Cipher must throw exeption if key not set";
    
    EXPECT_THROW(cipher->decrpyt(&in[0], &out[0], in.size()), std::exception)
            << "Cipher must throw exeption if key not set";

    cipher->set_key(key);

    EXPECT_NO_THROW(cipher->encrpyt(&in[0], &out[0], in.size()))
            << "Cipher must not throw exeption if key set";
    
    EXPECT_NO_THROW(cipher->decrpyt(&in[0], &out[0], in.size()))
            << "Cipher must not throw exeption if key set";

}

/* Some simple correcions check for Vigenere cipher */
TEST(Cryptor_Vigenere, Currecnes_simple)
{
    std::vector<uint8_t> in({1,2,3,4});
    std::vector<uint8_t> out(4);
    std::vector<uint8_t> key({4,3,2,1});
    auto cipher = cryptor::SubstitutionCipher::create("Vigenere");
   
    cipher->set_key(key);
    cipher->encrpyt(&in[0], &out[0], in.size());
    for(int i=0;i<4;i++){
        EXPECT_EQ(out[i], 5);
    }
    cipher->decrpyt(&out[0], &out[0], out.size());

    for(int i=0;i<4;i++){
        EXPECT_EQ(in[i], out[i]);
    }
}

inline void check_test_vector(std::string plain, std::string key, 
                        std::string encrypted)
{
    std::vector<uint8_t> in_data(plain.size());
    std::vector<uint8_t> exept_data(encrypted.size());
    std::vector<uint8_t> output_data(plain.size());
    std::vector<uint8_t> key_data(key.size());

    for(int i=0;i<plain.size();i++){
        in_data[i] = analyzer::Utils::letter_loockup(plain[i]);
    }

    for(int i=0;i<key.size();i++){
        key_data[i] = analyzer::Utils::letter_loockup(key[i]);
    }

    for(int i=0;i<encrypted.size();i++){
        exept_data[i] = analyzer::Utils::letter_loockup(encrypted[i]);
    }

    auto cipher = cryptor::SubstitutionCipher::create("Vigenere");
   
    cipher->set_key(key_data);
    cipher->encrpyt(&in_data[0], &output_data[0], in_data.size());
    for(int i=0;i<output_data.size();i++){
        EXPECT_EQ(output_data[i], exept_data[i]);
    }
    cipher->decrpyt(&output_data[0], &output_data[0], output_data.size());

    for(int i=0;i<in_data.size();i++){
        EXPECT_EQ(in_data[i], output_data[i]);
    }
}

/* Check test vector from https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher */
TEST(Cryptor_Vigenere, Currecnes_Wiki)
{
    std::string plain = "attackatdawn";
    std::string key = "LEMON";
    std::string encrypted = "LXFOPVEFRNHR";
    check_test_vector(plain, key, encrypted);
    plain = "ABCDABCDABCDABCDABCDABCDABCD";
    key = "cryptoisshortforcryptography";
    encrypted = "CSASTPKVSIQUTGQUCSASTPIUAQJB";
    check_test_vector(plain, key, encrypted);
    plain = "thequickbrownfoxjumpsoverthelazydog";
    key = "LION";
    encrypted = "EPSDFQQXMZCJYNCKUCACDWJRCBVRWINLOWU";
    check_test_vector(plain, key, encrypted);
}
