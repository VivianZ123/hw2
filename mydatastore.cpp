#include "mydatastore.h"
#include "util.h"
#include <vector>

MyDataStore::MyDataStore() {
}

MyDataStore::~MyDataStore() {
    vector<Product*>::iterator i = products.begin();
    while( i != products.end())
    {
        delete *i;
        ++i;
    }
    vector<User*>::iterator j = users.begin();
    while(j != users.end())
    {
        delete *j;
        ++j;
    }
}

void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
    set<string> keys= p->keywords();
    set<string>::iterator key_it= keys.begin();
    while(key_it != keys.end())
    {
        if (product_keyword.find(*key_it) == product_keyword.end())
        {
            set<Product*> keyhits;
            keyhits.insert(p);
            product_keyword.insert(make_pair(*key_it, keyhits));
        }
        else
        {
            (product_keyword.find(*key_it)->second).insert(p);
        }
        ++key_it;
    }  
}

void MyDataStore::addUser(User* u) {
    users.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> results;
    if (terms.empty()) {
        return std::vector<Product*>(results.begin(), results.end());
    }
    if (type == 0) {
        auto iter = terms.begin();
        if (products.find(*iter) != products.end()) {
            results = products[*iter];
        }
        ++iter;
        for (; iter != terms.end(); ++iter) {
            if (products.find(*iter) != products.end()) {
                results = setIntersection(results, products[*iter]);
            } else {
                results.clear();
                break;
            }
        }
    } else if (type == 1) {
        for (const auto& term : terms) {
            if (products.find(term) != products.end()) {
                results = setUnion(results, products[term]);
            }
        }
    }

    return std::vector<Product*>(results.begin(), results.end());
}


void MyDataStore::dump(std::ostream& ofile)
{
    vector<Product*>::iterator pt = products.begin();
    vector<User*>::iterator st = users.begin();
    ofile << "<products>"<<endl;
    while(pt != products.end())
    {
         (*pt)->dump(ofile);
         ++pt;
    }
    ofile << "</products>"<<endl;
    ofile << "<users>"<<endl;
    while(st != users.end())
    {
        (*st)->dump(ofile);
        ++st;
    }

    ofile << "</users>"<<endl;

    vector<Product*>::iterator rt = products.begin();
}

void MyDataStore::addToCart(std::string username, 
    unsigned int n_hit,std::vector<Product*> hits)
{

    vector<Product*> prod_new;
    if(carts.find(username) != carts.end()) 
    {
        carts.find(username)->second.push_back(hits[n_hit-1]);
    }
    else 
    {
        if(n_hit <= hits.size()) 
        { 
            prod_new.push_back(hits[n_hit-1]);
            carts.insert(make_pair(username, prod_new));
        }
    }

       
}
void MyDataStore::viewCart(std::string username)
{
    if(carts.find(username) != carts.end()) 
    { 
        vector<Product*> items = carts.find(username)->second;
        for(unsigned int i = 0; i < items.size(); i++) 
        {
            cout << "Item " << i+1 << endl
            items[i]->displayString() << endl<<endl;
        }
    }
}


