#include "shopping_db.h"

ShoppingDB::ShoppingDB() {

}

const std::vector<User *> &ShoppingDB::getUsers() const {
    return users;
}

void ShoppingDB::setUsers(const std::vector<User *> &users) {
    ShoppingDB::users = users;
}

const std::vector<Product *> &ShoppingDB::getProducts() const {
    return products;
}

void ShoppingDB::setProducts(const std::vector<Product *> &products) {
    ShoppingDB::products = products;
}

void ShoppingDB::addProduct(std::string name, int price) {
    products.push_back(new Product(name, price));
}

Product *ShoppingDB::findProduct(std::string name) {
    for(Product* product:products){
        if(product->name == name){
            return product;
        }
    }
    return nullptr;
}

void ShoppingDB::addUser(std::string username, std::string password, bool premium) {
    if(premium){
        users.push_back(new PremiumUser(username,password));
    } else{
        users.push_back(new NormalUser(username,password));
    }
}

User* ShoppingDB::findUser(std::string username) {
    for(User* user:users){
        if(user->name == username){
            return user;
        }
    }
    return nullptr;
}

std::vector<Product *> ShoppingDB::recommend(User *user) {
    return user->recommend(users);
}
