#include "mydatastore.h"
#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <iostream>
#include <fstream>


MyDataStore::~MyDataStore () {
  for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    delete *it;
  }
  for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    delete *it;
  }
}

    /**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p) {
  products_.insert(p);
  std::set<std::string> keySet = p->keywords();
  for (std::set<std::string>::iterator it = keySet.begin(); it != keySet.end(); ++it) {
    if (searchMap.find(*it) != searchMap.end()) { //if keyword is found
      searchMap.find(*it)->second.insert(p);
    } else {
      searchMap[*it] = std::set<Product*>();
      searchMap[*it].insert(p);
    }
  }
}

    /**
     * Adds a user to the data store
     */
void MyDataStore::addUser(User* u) {
  users_.insert(u);
  userCarts.insert(std::make_pair(u, std::vector<Product*>()));
}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {   //std::map<std::string, std::set<Product*>> searchMap
  //std::vector<Product*> currSearch; will be returned
  currSearch.clear();
  std::set<Product*> finalSet; //used to either union or intersection with other product results of keyword searches 
  std::set<Product*> workingSet; //used to gather products from current keyword search result
  for (size_t i = 0; i < terms.size(); i++) {
    workingSet.clear();
    if (searchMap.find(terms[i]) != searchMap.end()) { //if keyword is found within the search Map, add all the products associated with it to the workingSet
      workingSet = searchMap.find(terms[i])->second;
      if (type == 0) { //AND search (intersection)
        if (i == 0) {
          finalSet = workingSet;
        } else {
          finalSet = setIntersection(finalSet, workingSet);
        }
      } else { //OR search (union)
        finalSet = setUnion(finalSet, workingSet);
      }
    }
  } 
  //done gathering products in a set, now move it to a vector
  for (std::set<Product*>::iterator it = finalSet.begin(); it != finalSet.end(); ++it) {
    currSearch.push_back(*it);
  }
  return currSearch;
}

    /**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile) {
   ofile << "<products>" << std::endl;
  for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}

void MyDataStore::add_to_cart(const std::string& username, const int hit_result_index) {
  if (findUser(username) != NULL && hit_result_index <= currSearch.size()) {
    userCarts.find(findUser(username))->second.push_back(currSearch[hit_result_index-1]);
  } else {
    std::cout << "Invalid request" << std::endl;
  }
}

void MyDataStore::viewCart(const std::string& username) {
  if (findUser(username) != NULL) {
    std::vector<Product*> tempVector = userCarts.find(findUser(username))->second;
    for (size_t i = 0; i < tempVector.size(); i++) {
      std::cout << "Item " << i + 1 << std::endl;
      std::cout << tempVector[i]->displayString();
      std::cout << std::endl;
    }
  } else {
    std::cout << "Invalid username" << std::endl;
  }
}

void MyDataStore::buyCart(const std::string& username) {
  if (findUser(username) != NULL) {
    std::vector<Product*> tempVector = userCarts.find(findUser(username))->second;
    User* tempUser = userCarts.find(findUser(username))->first;
    std::vector<int> eraseIndexes;
    for (size_t i = 0; i < tempVector.size(); i++) {
      if (tempUser->getBalance() >= tempVector[i]->getPrice() && tempVector[i]->getQty() > 0) {
        tempUser->deductAmount(tempVector[i]->getPrice());
        tempVector[i]->subtractQty(1);
        eraseIndexes.push_back(i);
      }
    }
    if (eraseIndexes.size() > 0) {
      for (int i = eraseIndexes.size()-1; i >= 0; i--) {
        userCarts.find(findUser(username))->second.erase(userCarts.find(findUser(username))->second.begin() + eraseIndexes[i]);
      }
    }
  } else {
    std::cout << "Invalid username" << std::endl;
  }
}

User* MyDataStore::findUser(const std::string& username) {
  for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    if ((*it)->getName() == username) {
      return *it;
    }
  }
  return NULL;
}