#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream ifile("database.txt");
    stringstream ss;

    

    std::string wordString;
    std::string temp;

    while (!(ifile.fail())) {
      getline(ifile, temp);
      wordString += temp + " ";
    }

    std::set<std::string> myset = parseStringToWords(wordString);
    std::set<std::string>::iterator it = myset.begin();
    while (it != myset.end()) {
      cout << *it << endl;
      ++it;
    }
    return 0;
}
