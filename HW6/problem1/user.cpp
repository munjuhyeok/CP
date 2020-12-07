#include "user.h"

User::User(std::string name, std::string password): name(name), password(password) {

}

bool contains(std::vector<Product*> &products, Product* product){
    if(std::find(products.begin(), products.end(), product) != products.end()) {
        return true;
    } else {
        return false;
    }
}

int similarity(User* user1, User* user2){
    std::vector<Product*> products1 = user1->getHistory();
    std::vector<Product*> products2 = user2->getHistory();
    std::sort(products1.begin(), products1.end());
    std::sort(products2.begin(), products2.end());
//    std::unordered_set<Product*> products1(user1->getHistory().begin(), user1->getHistory().end());
//    std::unordered_set<Product*> products2(user2->getHistory().begin(), user2->getHistory().end());
    std::unordered_set<Product*> common_product;
    std::set_intersection(products1.begin(), products1.end(), products2.begin(), products2.end(), std::inserter(common_product, common_product.begin()));
    return common_product.size();
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

const std::vector<Product *> &User::getHistory() const {
    return history;
}

void User::setHistory(const std::vector<Product *> &history) {
    User::history = history;
}

void User::add_to_history(Product *product) {
    history.push_back(product);
}

NormalUser::NormalUser(const std::string &name, const std::string &password) : User(name, password) {}

int NormalUser::getPrice(Product * product) {
    return product->price;
}

std::vector<Product *> NormalUser::recommend(const std::vector<User *>& users) {
    std::vector<Product *> recommended_products;
    for (std::vector<Product *>::reverse_iterator i = history.rbegin(); i != history.rend(); ++i ) {
        Product* product = *i;
        if(!contains(recommended_products,product)){
            recommended_products.push_back(product);
        }
        if(recommended_products.size() == num_recommend){
            break;
        }
    }
    return recommended_products;
}

PremiumUser::PremiumUser(const std::string &name, const std::string &password) : User(name, password) {}

int PremiumUser::getPrice(Product * product) {
    return 5*(product->price*9/50);
}

std::vector<Product *> PremiumUser::recommend(const std::vector<User *>& users) {
    std::vector<Product *> recommended;
    std::vector<int> sim_recommended;
    for(User* user:users){
        if(user == this){
            continue;
        }
        int sim = similarity(this, user);
        Product* product = user->getHistory().back();
        if(contains(recommended, product)){
            continue;
        }
        int i = 0;
        for(i; i < sim_recommended.size(); i++){
            if(sim > sim_recommended[i]){
                sim_recommended.insert(sim_recommended.begin() + i, sim);
                recommended.insert(recommended.begin() + i, product);
                break;
            }
        }
        if(i == recommended.size() && i != num_recommend){
            sim_recommended.push_back(sim);
            recommended.push_back(product);
        }
        if(sim_recommended.size() == num_recommend + 1){
            sim_recommended.pop_back();
            recommended.pop_back();
        }
    }
    return recommended;
}
