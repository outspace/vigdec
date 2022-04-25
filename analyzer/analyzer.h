#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include "ngram.h"

namespace analyzer {

  typedef std::pair < float, std::vector < uint8_t >> key_stat;
  typedef std::priority_queue < key_stat, std::vector < key_stat > ,
    std::greater < key_stat >> key_stat_heap;

  class Analyzer {
    public:
      static const uint8_t ALPHABETSIZE = 26;
      uint32_t HEAPSIZE = 100;
      uint32_t MAXKEYSIZE = 12;
      Analyzer();
      Analyzer(const std::string file_name);
      void load_cipher_text(const std::string file_name);
      void load_statistic_file(std::string bigram_fn, std::string thrigram_fn,
        std::string quadgram_fn);
      std::vector < char > get_key();
      std::vector < char > get_plain_text();
      void proccess();
      ~Analyzer();

    private:
      void add_candidate(key_stat_heap & heap, key_stat);
      std::vector < char > m_cipher_text;
      std::vector < uint8_t > m_cipher_text_data;
      std::vector < char > m_key;
      std::vector < uint8_t > m_key_data;
      std::vector < char > m_plain_text;
      uint32_t m_max_candidates_sz;
      key_stat_heap m_candidates;
      NgramStatistics m_bigram;
      NgramStatistics m_trigram;
      NgramStatistics m_quadgram;
  };

}