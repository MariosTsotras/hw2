#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::string cleanedWords = convToLower(rawWords);
  cleanedWords = trim(cleanedWords);
  std::set<std::string> keywords;
  std::size_t index = 0;
  std::string currKey = "";
  while (index < cleanedWords.size()) {
    char currChar = cleanedWords[index];
    if ((currChar >= 97 && currChar <= 122) || (currChar >= 48 && currChar <= 57)) {
      currKey.push_back(currChar);
    } else {
      if (currKey.size() >= 2) { 
        keywords.insert(currKey);
      }
      currKey = "";
    }
    index++;
  }
  
  if (currKey.size() >= 2) { 
    keywords.insert(currKey);
  }

  return keywords;







}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
