#include "mydatastore.h"
//#include "util.h"
#include <vector>
using namespace std;
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
    set<Product*> set_sol;
    vector<Product*> results;

    if (terms.empty())
    {
        return results;
    } 
    
    if (type == 0)
    {
        set<Product*> set_and;
        for (unsigned int i = 0; i < terms.size(); i++)
        {

            if(set_and.empty())
            {
                set_and = product_keyword[terms[i]];
            }
            
            set_and = setIntersection(product_keyword[terms[i]],set_and);   
        }
        set_sol = set_and;
    }
    else if (type == 1)
    {
        set<Product*> set_or;

        for (unsigned int i = 0; i < terms.size(); i++)
        {
            set_or = setUnion(product_keyword[terms[i]],set_or);
        }
        set_sol = set_or;
    }
    set<Product*>::iterator it = set_sol.begin();
    while(it != set_sol.end())
    {
        results.push_back(*it);
        ++it;
    }
    return results;
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
}

User* MyDataStore::findUserByName(const std::string& username) {
    for(unsigned int i = 0; i < users.size(); i++) {
        if(users[i]->getName() == username) {
            return users[i];
        }
    }
    return nullptr; 
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
            cout << "Item " << i+1 << endl;
            cout << items[i]->displayString() << endl;
        }
    }
}
void MyDataStore::buyCart(std::string username)
{
   
    map<string, vector<Product*> >::iterator it = carts.find(username);
    User* user; 

    if(carts[username].size() <= 0) 
    {
        return;
    }   
    for(unsigned int i = 0; i < users.size(); i++) 
    {
        if(users[i]->getName() == username)
        {
            user = users[i];
        }
    }
    vector<Product*> &useritems = it->second; 
    vector<Product*>::iterator item = useritems.begin();
    unsigned int i = 0;

    while( i < useritems.size() ) 
    {
        double price = useritems[i]->getPrice();
        if(user->getBalance() >= price && (useritems[i]->getQty() != 0)) 
        { 
            useritems[i]->subtractQty(1);
            user->deductAmount(price);
            for(unsigned int k =0;k<i;k++)
            {
                item++;
            }
            useritems.erase(item); 
             
        } 
        else
        {
            i++;
        }
    }
}


