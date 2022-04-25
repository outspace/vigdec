#include "analyzer.h"
#include "utils.h"
#include <vector>
#include <string>

static
const char usage[] =
  "usage:\n"
  "./vigdec cipher_text_file [heapsize]\n\n"
  "-cipher_text_file is path to file that contains English text encrypted with Vigenere cipher.\n"
  "-heapsize is digit. Optional parameter that varieties correctness and time/memory complexity.\n"
  "By default is 100. Increasing this parameter can give better result but will take more time.\n"
  "You can decrease or increase this parameter to fit your limits. \n";

int main(int argc, char * argv[]) {
  // Check for correct number of command line arguments
  if (argc < 2 || argc > 3) {
    std::cout << usage << std::endl;
    return 1;
  }

  int numChar = 0;
  int keylength;
  char letter;
  std::string fileName;
  std::vector < char > ciphertext;
  std::vector < char > keyLetters;

  // get the filename from command line
  fileName = argv[1];

  analyzer::Analyzer decoder(fileName);

  //Set Heap size from command line 
  if (argc == 3) {
    std::string arg = argv[2];
    std::size_t pos;
    int x = std::stoi(arg, & pos);
    if (pos < arg.size() || x <= 0) {
      std::cout << usage << std::endl;
      return 1;
    }
    decoder.HEAPSIZE = x;
  }

  decoder.load_statistic_file("english_bigrams.txt", "english_trigrams.txt",
    "english_quadgrams.txt");

  decoder.proccess();

  std::vector < char > result_key = decoder.get_key();
  std::vector < char > result_plain = decoder.get_plain_text();

  if (result_key.size() > 0) {
    // Case when we have one letter key
    // In that case it will give two same letters
    if (result_key.size() == 2) {
      if (result_key[0] == result_key[1]) {
        result_key.pop_back();
      }
    }
    std::cout << "Key: " << std::string(result_key.begin(), result_key.end()) << std::endl;
    std::cout << "Plaintext:" << std::endl << std::string(result_plain.begin(), result_plain.end()) << std::endl;
  } else {
    // Result text statistic is too bad and we don't find key
    std::cout << "Key not found. It was too hard 4 me, mb try bigger heap size :)" << std::endl;
  }

  // quit
  return 0;
}