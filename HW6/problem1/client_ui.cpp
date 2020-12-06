#include <vector>
#include "client_ui.h"
#include "product.h"
#include "user.h"

ClientUI::ClientUI(ShoppingDB &db, std::ostream& os) : UI(db, os), current_user() { }

ClientUI::~ClientUI() {
    delete current_user;
}

int discount(int price){
    return 5*(price*9/50);
}

bool premium(User* user){
    PremiumUser* temp = dynamic_cast<PremiumUser*>(user);
    return temp != NULL;
}

void ClientUI::signup(std::string username, std::string password, bool premium) {
    // TODO: For problem 1-2
    db.addUser(username,password,premium);
    os<<"CLIENT_UI: "<<username<<" is signed up.\n";
}

void ClientUI::login(std::string username, std::string password) {
    // TODO: For problem 1-2
    if(current_user != nullptr){
        os<<"CLIENT_UI: Please logout first.\n";
        return;
    }
    User* user = db.findUser(username);
    if(user != nullptr && user->verify(password)){
        current_user = user;
        os<<"CLIENT_UI: "<< username<<" is logged in.\n";
    } else{
        os<<"CLIENT_UI: Invalid username or password.\n";
    }
}

void ClientUI::logout() {
    // TODO: For problem 1-2
    if(current_user != nullptr){
        os<<"CLIENT_UI: "<< current_user->name<<" is logged out.\n";
        current_user = nullptr;
    } else{
        os<<"CLIENT_UI: There is no logged-in user.\n";
    }
}

void ClientUI::add_to_cart(std::string product_name) {
    // TODO: For problem 1-2
    if(current_user != nullptr){
        Product* product = db.findProduct(product_name);
        if(product != nullptr) {
            current_user->add_to_cart(product);
            os<<"CLIENT_UI: "<<product_name<<" is added to the cart.\n";
        } else{
            os<<"CLIENT_UI: Invalid product name.\n";
            return;
        }
    } else{
        os<<"CLIENT_UI: Please login first.\n";
    }
}

void ClientUI::list_cart_products() {
    // TODO: For problem 1-2.
    if(current_user != nullptr){
        os<<"CLIENT_UI: Cart: [";
        std::vector<Product *> products = current_user->getCart();
        int num_products = products.size();
        for (int i = 0; i<num_products - 1; i++){
            Product *product = products[i];
            int price = current_user->getPrice(product);
            os<<"("<<product->name<<", "<<price<<"), ";
        }
        Product *product = products[num_products - 1];
        int price = current_user->getPrice(product);
        os<<"("<<product->name<<", "<<price<<")";
        os<<"]\n";
    } else{
        os<<"CLIENT_UI: Please login first.\n";
    }
}

void ClientUI::buy_all_in_cart() {
    // TODO: For problem 1-2
    if(current_user != nullptr){
        int price_sum = 0;
        std::vector<Product *> products = current_user->getCart();
        for (Product* product:products){
            int price = current_user->getPrice(product);
            price_sum += price;
        }
        os<<"CLIENT_UI: Cart purchase completed. Total price: "<<price_sum<<".\n";
        current_user->setCart(std::vector<Product*>());
    } else{
        os<<"CLIENT_UI: Please login first.\n";
    }
}

void ClientUI::buy(std::string product_name) {
    // TODO: For problem 1-2
    if(current_user != nullptr){
        Product* product = db.findProduct(product_name);
        if(product != nullptr) {
            int price = current_user->getPrice(product);
            os<<"CLIENT_UI: Purchase completed. Price: "<<price<<".\n";
        } else{
            os<<"CLIENT_UI: Invalid product name.\n";
            return;
        }
    } else{
        os<<"CLIENT_UI: Please login first.\n";
    }
}

void ClientUI::recommend_products() {
    // TODO: For problem 1-3.
    if(current_user != nullptr){

    } else{
        os<<"CLIENT_UI: Please login first.\n";
    }
}

