#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string& name, double price, int qty, const std::string& ISBN, const std::string& author)
    : Product(category, name, price, qty), ISBN_(ISBN), author_(author) {}

Book::~Book()
{
}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_ + " " + ISBN_);
    keys.insert(author_);
    return keys;
}

std::string Book::displayString() const {
    return name_ + "\n" + "Author: " + ISBN_ + " " + "ISBN: " + author_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_)+" left.";
}

void Book::dump(std::ostream& os) const {
    //Product::dump(os);
    //std::cout << "Book: " << displayString() << std::endl;
    //os << ISBN_ << author_ << std::endl;
    os << category_ << endl << name_ << endl
	  << price_ << endl << qty_ << endl;
	  os << author_ << endl << ISBN_ << endl;
}
