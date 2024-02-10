#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}


/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Clothing::keywords() const {
  std::set<std::string> keywordSet = parseStringToWords(name_ + " " + size_ + " " + brand_);
  return keywordSet;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const {
  std::string display = name_; 
  display = display + "\n" + "Size: " + size_+ " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return display;
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}


