#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore{
public:

    ~MyDataStore();
    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void add_to_cart(const std::string& username, const int hit_result_index);

    void viewCart(const std::string& username);

    void buyCart(const std::string& username);

    User* findUser(const std::string& username);
private:
  std::set<Product*> products_;
  std::set<User*> users_;
  std::map<std::string, std::set<Product*>> searchMap;
  std::map<User*, std::vector<Product*>> userCarts;
  std::vector<Product*> currSearch;

};

#endif
