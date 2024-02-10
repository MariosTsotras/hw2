#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}


/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords() const {
  std::set<std::string> keywordSet = parseStringToWords(name_ + " " + author_);
  keywordSet.insert(isbn_);
  return keywordSet;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const {
  std::string display = name_; 
  display = display + "\n" + "Author: " + author_+ " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return display;
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}


