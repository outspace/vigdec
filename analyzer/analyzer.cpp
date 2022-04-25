#include <numeric>

#include <algorithm>
#include <iostream>
#include "analyzer.h"
#include "scanner.h"
#include "../crypto/subst_cipher.h"

namespace analyzer {

  Analyzer::Analyzer() {};

  Analyzer::Analyzer(const std::string file_name) {
    load_cipher_text(file_name);
  }

  void Analyzer::load_cipher_text(std::string file_name) {
    // Open file
    Scanner inStream;
    inStream.open_file(file_name);

    // Add each character from file to ciphertext vector, removing newlines and spaces
    while (inStream.has_more_data()) {
      char letter = inStream.next_char();
      if (letter == '\n' || letter == ' ') {
        continue;
      }
      m_cipher_text.push_back(letter);
    }

    // Close the input stream
    inStream.close();

    // Don't need to analyze full text, use first 250 letters 
    for(int i=0;((i<250) && (i<m_cipher_text.size()));i++){
      m_cipher_text_data.push_back(Utils::letter_loockup(m_cipher_text[i]));
    }
  }

  void Analyzer::load_statistic_file(std::string bigram_fn, std::string thrigram_fn,
    std::string quadgram_fn) {
    m_bigram.load_statistic_file(bigram_fn);
    m_trigram.load_statistic_file(thrigram_fn);
    m_quadgram.load_statistic_file(quadgram_fn);
  }

  void Analyzer::add_candidate(key_stat_heap & heap, key_stat candidate) {
    if (heap.size() < HEAPSIZE) {
      heap.push(candidate);
    } else {
      if (heap.top().first < candidate.first) {
        heap.pop();
        heap.push(candidate);
      }
    }
  }

  void Analyzer::proccess() {
    auto vigener = cryptor::SubstitutionCipher::create("Vigenere");
    std::vector < uint8_t > bestKey;
    float bestProb = -std::numeric_limits < float > ::infinity();
    for (int keyLen = 2; keyLen <= MAXKEYSIZE; keyLen++) {
      m_candidates = key_stat_heap();

      // bigram - for bitext
      for (uint8_t first_char = 0; first_char < ALPHABETSIZE; first_char++) {
        for (uint8_t second_char = 0; second_char < ALPHABETSIZE; second_char++) {

          std::vector < uint8_t > bigramd(2);
          bigramd[0] = first_char;
          bigramd[1] = second_char;
          std::vector < uint8_t > patern(bigramd);
          patern.resize(keyLen, 0);

          vigener -> set_key(patern);
          std::vector < uint8_t > dec_patern(m_cipher_text_data.size());
          vigener -> decrpyt( & m_cipher_text_data[0], & dec_patern[0], m_cipher_text_data.size());

          float score = m_bigram.getScore(dec_patern, patern.size());
          key_stat new_candidate = std::make_pair(score, bigramd);
          add_candidate(m_candidates, new_candidate);
        }
      }

      // trigram - for tritext
      if (keyLen >= 3) {
        key_stat_heap new_candidates;
        while (!m_candidates.empty()) {
          key_stat cur_candidate = m_candidates.top();
          m_candidates.pop();
          for (uint8_t character = 0; character < ALPHABETSIZE; character++) {
            std::vector < uint8_t > newKey(cur_candidate.second);
            newKey.push_back(character);
            std::vector < uint8_t > patern(newKey);
            patern.resize(keyLen, 0);

            auto vigener = cryptor::SubstitutionCipher::create("Vigenere");
            vigener -> set_key(patern);
            std::vector < uint8_t > dec_patern(m_cipher_text_data.size());
            vigener -> decrpyt( & m_cipher_text_data[0], & dec_patern[0], m_cipher_text_data.size());

            float score = m_trigram.getScore(dec_patern, patern.size());
            key_stat new_candidate = std::make_pair(score, newKey);
            add_candidate(new_candidates, new_candidate);
          }
        }
        new_candidates.swap(m_candidates);
      }

      // quadgram - for quadtext and beyond
      for (int k = 4; k <= keyLen; k++) {
        key_stat_heap new_candidates;
        while (!m_candidates.empty()) {
          key_stat cur_candidate = m_candidates.top();
          m_candidates.pop();
          for (uint8_t character = 0; character < ALPHABETSIZE; character++) {
            std::vector < uint8_t > newKey(cur_candidate.second);
            newKey.push_back(character);
            std::vector < uint8_t > patern(newKey);
            patern.resize(keyLen, 0);

            vigener -> set_key(patern);
            std::vector < uint8_t > dec_patern(m_cipher_text_data.size());
            vigener -> decrpyt( & m_cipher_text_data[0], & dec_patern[0], m_cipher_text_data.size());

            float score = m_quadgram.getScore(dec_patern, patern.size());
            key_stat new_candidate = std::make_pair(score, newKey);
            add_candidate(new_candidates, new_candidate);
          }
        }
        new_candidates.swap(m_candidates);
      }

      // Find best candidate for this key length
      key_stat_heap new_candidates;
      while (!m_candidates.empty()) {
        key_stat cur_candidate = m_candidates.top();
        std::vector < uint8_t > plain_text(m_cipher_text_data.size());

        vigener -> set_key(cur_candidate.second);
        std::vector < uint8_t > dec_patern(m_cipher_text_data.size());
        vigener -> decrpyt( & m_cipher_text_data[0], & plain_text[0], m_cipher_text_data.size());

        float curProb = 0.0;
        for (int i = 0; i <= plain_text.size() - 4; i += 1) {
          std::vector < uint8_t > word(4);
          for (int j = 0; j < 4; j++) {
            word[j] = plain_text[i + j];
          }
          curProb += m_quadgram.getScore(word, 4);
        }
        if (curProb > bestProb) {
          bestKey = cur_candidate.second;
          bestProb = curProb;
        }
        m_candidates.pop();
      }
    }
      m_cipher_text_data.clear();
      for (auto & it: m_cipher_text) {
        m_cipher_text_data.push_back(Utils::letter_loockup(it));
      }
    
      // Save results
      bestKey.swap(m_key_data);
      vigener -> set_key(m_key_data);
      std::vector < uint8_t > plain_data(m_cipher_text_data.size());
      vigener -> decrpyt( & m_cipher_text_data[0], & plain_data[0], m_cipher_text_data.size());
      m_plain_text.resize(m_cipher_text_data.size());
      for (int i = 0; i < m_cipher_text_data.size(); i++) {
        m_plain_text[i] = Utils::num_loockup(plain_data[i]);
      }
      m_key.resize(m_key_data.size());
      for (int i = 0; i < m_key_data.size(); i++) {
        m_key[i] = Utils::num_loockup(m_key_data[i]);
      }

  }

  /* Get result key */
  std::vector < char > Analyzer::get_key() {
    return m_key;
  }

  /* Get decoded text */
  std::vector < char > Analyzer::get_plain_text() {
    return m_plain_text;
  }

  Analyzer::~Analyzer() {};
}