#include "book.h"
#include "util.h"

Book::Book(const std::string& name, double price, int qty, const std::string& ISBN, const std::string& author)
    : Product("Book", name, price, qty), ISBN_(ISBN), author_(author) {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_ + " " + author_);
    keys.insert(ISBN_);
    return keys;
}

std::string Book::displayString() const {
    return name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + ISBN_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_)+" left.";
}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    std::cout << "Book: " << displayString() << std::endl;
    os << "ISBN: " << ISBN_ << "\nAuthor: " << author_ << std::endl;
}
