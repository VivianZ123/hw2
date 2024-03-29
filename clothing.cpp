#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string& name, double price, int qty, const std::string& size, const std::string& brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_ + " " + brand_);
    return keys;
}

std::string Clothing::displayString() const {
    return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) +" left.";
}

void Clothing::dump(std::ostream& os) const {
    //Product::dump(os);
    //os <<  size_ << brand_ << std::endl;
    os << category_ << endl << name_ << endl
	  << price_ << endl << qty_ << endl;
	  os << size_ << endl << brand_ << endl;
}