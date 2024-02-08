#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <queue>
#include "product.h"
#include <map>
#include <queue>
#include <algorithm>
#include <cctype> 

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();
    void addToCart(std::vector<Product*>& hits, int hitIndex);
    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);

private:
    std::vector<Product*> cart;
    std::string name_;
    double balance_;
    int type_;
};
#endif
