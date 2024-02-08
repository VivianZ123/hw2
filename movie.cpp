#include "movie.h"
#include "util.h"

Movie::Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating)
    : Product("Movie", name, price, qty), genre_(genre), rating_(rating) {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    keys.insert(genre_);
    return keys;
}

std::string Movie::displayString() const {
    return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_)+" left.";
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << "Genre: " << genre_ << "\nRating: " << rating_ << std::endl;
}