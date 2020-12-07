#ifndef PROBLEM1_USER_H
#define PROBLEM1_USER_H

#include <string>
#include <vector>
#include "product.h"
#include <algorithm>
#include <unordered_set>

class User {
public:
    User(std::string name, std::string password);

    const std::string name;

    bool verify(std::string password);

private:
    std::string password;
protected:
    int num_recommend = 3;
    std::vector<Product *> cart;
    std::vector<Product *> history;
public:
    const std::vector<Product *> &getHistory() const;

    void setHistory(const std::vector<Product *> &history);

    void add_to_history(Product* product);

    const std::vector<Product *> &getCart() const;

    void setCart(const std::vector<Product *> &cart);

    void add_to_cart(Product *product);

    virtual int getPrice(Product*) = 0;
    virtual std::vector<Product *> recommend(const std::vector<User*> &users) = 0;

};

class NormalUser : public User {
public:
    NormalUser(const std::string &name, const std::string &password);
    int getPrice(Product*) override;
    std::vector<Product *> recommend(const std::vector<User*> &users) override;
};

class PremiumUser : public User {
public:
    PremiumUser(const std::string &name, const std::string &password);
    int getPrice(Product*) override;
    std::vector<Product *> recommend(const std::vector<User*> &users) override;
};

#endif //PROBLEM1_USER_H
