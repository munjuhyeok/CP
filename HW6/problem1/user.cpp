#include "user.h"

User::User(std::string name, std::string password): name(name), password(password) {

}

bool User::verify(std::string password) {
    return password == this->password;
}

const std::vector<Product *> &User::getCart() const {
    return cart;
}

void User::setCart(const std::vector<Product *> &cart) {
    User::cart = cart;
}

void User::add_to_cart(Product* product) {
    cart.push_back(product);
}

NormalUser::NormalUser(const std::string &name, const std::string &password) : User(name, password) {}

int NormalUser::getPrice(Product * product) {
    return product->price;
}

PremiumUser::PremiumUser(const std::string &name, const std::string &password) : User(name, password) {}

int PremiumUser::getPrice(Product * product) {
    return 5*(product->price*9/50);
}
