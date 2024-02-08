#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string& name, double price, int qty, const std::string& genre, const std::string& rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_ +" "+genre_ );
    return keys;
}

std::string Movie::displayString() const {
    return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_)+" left.";
}

void Movie::dump(std::ostream& os) const {
    //Product::dump(os);
    //os << genre_ << rating_ << std::endl;
    os << category_ << endl << name_ << endl
	  << price_ << endl << qty_ << endl;
	  os << genre_ << endl << rating_ << endl;
}