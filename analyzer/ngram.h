#include <string>
#include <map>
#include <vector>

namespace analyzer {
  class NgramStatistics {
    public:
      NgramStatistics();
      NgramStatistics(std::string file_name);
      void load_statistic_file(std::string file_name);
      float getScore(std::vector < uint8_t > text, int shift);
      ~NgramStatistics();
    private:
      std::map < uint64_t, uint64_t > m_ngramMap;
      std::map < uint64_t, float > m_ngramProbMap;
      uint64_t m_total_freq;
      uint8_t m_gram_sz;
      float m_min_score;
  };
}