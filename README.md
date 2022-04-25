# vigdec

## vigdec – tool that breaks Vigenère cipher without knowing the key.

project consist of three parts:
- cryptor – library that used for crypto operation (Vigenère cipher
implementation)
- analyzer – class with decoder algorithm and console application.
- test – testsuite based on gTest

## Algorithm:

Decryption algorithm based on local random search technique. Text “fitness” fitness
measure based on quadgram statistics.

## Detailed algorithm description:
http://www.practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-vigenere-cipher-part-2/

This technique gives much better results than other standard algorithms. Around 35
letters is enough for stably decryption. Sometimes it works with less size of text but it
depends on text quality and it’s quadgram statistics.

## Usage:
```
./vigdec cipher_text_file [heapsize]
-cipher_text_file is a path to file that contains English text encrypted with Vigenere
cipher.
-heapsize is a digit. Optional parameter that varieties correctness and time/memory
complexity.
By default it is 100. Increasing this parameter can give better results but will take
more time. You can decrease or increase this parameter to fit your time/memory
limits.
```
## Limitations:
- The key length is limited by 12 symbols. It’s hard coded and can be
increased. In this project it’s limited by the task description.
- Application require additional files with bigrams, trigrams and quadgrams
statistics. These files are included into the project and their names are hard
coded. That’s why you need to start application in directory that contains this
files.
- The language for text is English. Algorithm can be applied for any language
but it requires some changes (alphabet letter count and n-gram statistic files
for this language).

## Building:
requires: C++11, cmake, pthread.
```
extract vigdec.zip
cd vigdec
cmake .
make
```
Tested on Ubuntu 20.10, should work on other OS.

## Examples:

Test text taken from
https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Examples.html (example 2. other text has larger key length than in limits).
```
osboxes@osboxes:~/test/vigdec$ ./vigdec testdata/testdata.txt
Key: UNITEDSTATES
Plaintext:
WETHEREFORETHEREPRESENTATIVESOFTHEUNITEDSTATESOFAMERICAINGENERALCONGRESSASS
EMBLEDAPPEALINGTOTHESUPREMEJUDGEOFTHEWORLDFORTHERECTITUDEOFOURINTENTIONSDOI
NTHENAMEANDBYAUTHORITYOFTHEGOODPEOPLEOFTHESECOLONIESSOLEMNLYPUBLISHANDDECL
ARETHATTHESEUNITEDCOLONIESAREANDOFRIGHTOUGHTTOBEFREEANDINDEPENDENTSTATESTHAT
THEYAREABSOLVEDFROMALLALLEGIANCETOTHEBRITISHCROWNANDTHATALLPOLITICALCONNECTIO
NBETWEENTHEMANDTHESTATEOFGREATBRITAINISANDOUGHTTOBETOTALLYDISSOLVEDANDTHATASF
REEANDINDEPENDENTSTATESTHEYHAVEFULLPOWERTOLEVYWARCONCLUDEPEACECONTRACTALLIA
NCESESTABLISHCOMMERCEANDTODOALLOTHERACTSANDTHINGSWHICHINDEPENDENTSTATESMAYO
FRIGHTDOANDFORTHESUPPORTOFTHISDECLARATIONWITHAFIRMRELIANCEONTHEPROTECTIONOFDI
VINEPROVIDENCEWEMUTUALLYPLEDGETOEACHOTHEROURLIVESOURFORTUNESANDOURSACREDH
ONOR
Same text cutted into 44 letters
osboxes@osboxes:~/test/vigdec$ ./vigdec testdata/testdata6.txt
Key: UNITEDSTATES
Plaintext:
WETHEREFORETHEREPRESENTATIVESOFTHEUNITEDSTA
```

Also it can be checked with https://www.guballa.de/vigenere-solver. Directory testdata contains some test ciphertexts.
