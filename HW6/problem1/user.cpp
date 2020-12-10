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

int indexOf(std::vector<Product*> &products, Product* product){ //return -1 if doesn't exist
    for(int i = 0; i<products.size(); i++){
        if(products[i] == product){
            return i;
        }
    }
    return -1;
}

int similarity(const User* user1, const User* user2){
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
    std::vector<Product *> recommended;
    for (std::vector<Product *>::reverse_iterator i = history.rbegin(); i != history.rend(); ++i ) {
        Product* product = *i;
//        if(!contains(recommended,product)){
        if(indexOf(recommended,product)==-1){
            recommended.push_back(product);
        }
        if(recommended.size() == num_recommend){
            break;
        }
    }
    return recommended;
}

PremiumUser::PremiumUser(const std::string &name, const std::string &password) : User(name, password) {}

int PremiumUser::getPrice(Product * product) {
    return round((float)product->price*9/10);
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
//        if(contains(recommended, product)){
//            continue;
//        }
        int index = indexOf(recommended, product);
//        if(index == -1){ //product was not recommended
//            int i = 0;
//            for(i; i < sim_recommended.size(); i++){
//                if(sim > sim_recommended[i]){
//                    sim_recommended.insert(sim_recommended.begin() + i, sim);
//                    recommended.insert(recommended.begin() + i, product);
//                    break;
//                }
//            }
//            if(i == recommended.size()){
//                sim_recommended.push_back(sim);
//                recommended.push_back(product);
//            }
        if(index != -1){ //product was recommended before
            int sim_previous = sim_recommended[index];
            if(sim <= sim_previous){
                continue;
            } else{
                sim_recommended.erase(sim_recommended.begin()+index);
                recommended.erase(recommended.begin()+index);
            }
        }
        int i = 0;
        for(i; i < sim_recommended.size(); i++){
            if(sim > sim_recommended[i]){
                sim_recommended.insert(sim_recommended.begin() + i, sim);
                recommended.insert(recommended.begin() + i, product);
                break;
            }
        }
        if(i == recommended.size()){
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
