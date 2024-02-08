#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    User* findUserByName(const std::string& username);
    void addToCart(std::string username,  
        unsigned int hit_index, std::vector<Product*> hits);
    void viewCart(std::string username);
    void buyCart(std::string username);

private:
    std::map<std::string, std::set<Product*> > product_keyword;
    std::map<std::string, std::vector<Product*> > carts;
    std::vector<Product*> products;
    std::vector<User*> users;
};

#endif