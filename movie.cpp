#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}


/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const {
  std::set<std::string> keywordSet = parseStringToWords(name_ + " " + genre_);
  return keywordSet;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const {
  std::string display = name_; 
  display = display + "\n" + "Genre: " + genre_+ " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return display;
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}


