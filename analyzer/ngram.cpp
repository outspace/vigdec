#include "ngram.h"
#include "scanner.h"
#include <cmath>

namespace analyzer {
  NgramStatistics::NgramStatistics() {};

  NgramStatistics::~NgramStatistics() {};

  /* Load file with gramm frequency */
  void NgramStatistics::load_statistic_file(std::string file_name) {
    m_total_freq = 0;
    m_gram_sz = 0;
    Scanner inStream;

    // read file
    inStream.open_file(file_name);
    while (inStream.has_more_data()) {
      std::string gramm = inStream.next();
      if (!gramm.empty()) {
        uint64_t freq = inStream.next_long();
        uint64_t patern = 0;
        for (int i = 0; i < gramm.size(); i++) {
          patern += ((gramm[i] - 'A') << (i * 8));
        }
        m_ngramMap[patern] = freq;
        m_total_freq += freq;
        m_gram_sz = std::max(m_gram_sz, (uint8_t) gramm.size());
      }
    }
    inStream.close();

    // calculate probabilities
    // 1. for words in ngramFile
    for (const auto & kv: m_ngramMap) {
      m_ngramProbMap[kv.first] = log10(float(kv.second) / m_total_freq);
    }

    // 2. for words not in ngramFile: min probability for frequency of 0
    m_min_score = log10(float(0.01) / m_total_freq);
  }

  NgramStatistics::NgramStatistics(std::string file_name) {
    load_statistic_file(file_name);
  }

  /* Get the score of the input text */
  float NgramStatistics::getScore(std::vector < uint8_t > text, int shift) {
    float score = 0.0;
    for (int i = 0; i <= text.size() - m_gram_sz; i += shift) {
      for (int k = 0; k <= shift - m_gram_sz; k++) {
        uint64_t word = 0;
        for (int j = 0; j < m_gram_sz; j++) {
          word += (text[i + k + j] << (j * 8));
        }
        if (m_ngramProbMap.count(word)) {
          score += m_ngramProbMap[word];
        } else {
          score += m_min_score;
        }
      }
    }
    return score;
  }
}