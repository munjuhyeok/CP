#ifndef PROBLEM1_SHOPPING_DB_H
#define PROBLEM1_SHOPPING_DB_H

#include <string>
#include <vector>
#include "user.h"
#include "product.h"

class ShoppingDB {
public:
    ShoppingDB();

    const std::vector<User *> &getUsers() const;

    void setUsers(const std::vector<User *> &users);

    const std::vector<Product *> &getProducts() const;

    void setProducts(const std::vector<Product *> &products);

    void addProduct(std::string name, int price);

    Product* findProduct(std::string name);

    void addUser(std::string username, std::string password, bool premium);

    User* findUser(std::string username);

    std::vector<Product *> recommend(User* user);
private:
    std::vector<User*> users;
    std::vector<Product*> products;

};

#endif //PROBLEM1_SHOPPING_DB_H
