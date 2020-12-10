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


int similarity_between(const User* user1, const User* user2){
    std::vector<Product*> products1 = user1->getHistory();
    std::vector<Product*> products2 = user2->getHistory();
    std::sort(products1.begin(), products1.end());
    std::sort(products2.begin(), products2.end());
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
        if(!contains(recommended,product)){
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
    std::vector<int> sims;
    for(User* user:users) {
        if (user == this) {
            sims.push_back(-1); //do not consider user himself
            continue;
        }
        int sim = similarity_between(this, user);
        sims.push_back(sim);
    }

    while(true){
        int sim = *std::max_element(sims.begin(), sims.end());
        if(sim == -1){ //no more user to consider
            break;
        }
        int index_max_sim = std::max_element(sims.begin(), sims.end()) - sims.begin();

        std::vector<Product *> history = users[index_max_sim]->getHistory();
        if(history.size()==0){
            sims[index_max_sim] = -1; //do not consider this user next time
            continue;
        }

        Product* product = history.back();
        if(!contains(recommended, product)){
            recommended.push_back(product);
        }
        if(recommended.size() == num_recommend){
            break;
        }
        sims[index_max_sim] = -1; //do not consider this user next time
    }
    return recommended;
}
