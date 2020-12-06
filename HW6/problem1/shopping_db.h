#ifndef PROBLEM1_SHOPPING_DB_H
#define PROBLEM1_SHOPPING_DB_H

#include <string>
#include <vector>
#include "user.h"
#include "product.h"

class ShoppingDB {
public:
    ShoppingDB();
private:
    std::vector<User*> users;
public:
    const std::vector<User *> &getUsers() const;

    void setUsers(const std::vector<User *> &users);

    const std::vector<Product *> &getProducts() const;

    void setProducts(const std::vector<Product *> &products);

    void addProduct(std::string name, int price);

    Product* findProduct(std::string name);

    bool editProduct(std::string name, int price); //return whether product with name exists.

    void addUser(std::string username, std::string password, bool premium);

    User* findUser(std::string username);


private:
    std::vector<Product*> products;
};

#endif //PROBLEM1_SHOPPING_DB_H
