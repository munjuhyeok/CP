#include "admin_ui.h"

AdminUI::AdminUI(ShoppingDB &db, std::ostream& os): UI(db, os) { }

void AdminUI::add_product(std::string name, int price) {
    // TODO: For problem 1-1
    db.addProduct(name, price);
    if (price > 0) {
        os << "ADMIN_UI: " << name << " is added to the database.\n";
    } else{
        os << "ADMIN_UI: Invalid price.\n";
    }
}
void AdminUI::edit_product(std::string name, int price) {
    // TODO: For problem 1-1

    if (db.editProduct(name, price)) {
        os << "ADMIN_UI: " << name << " is modified from the database.\n";
        if(price<=0) {
            os<<"ADMIN_UI: Invalid price.\n";
        }
    }else{
        os<<"ADMIN_UI: invalid product name.\n";
    }
}

void AdminUI::list_products() {
    // TODO: For problem 1-1
    os<<"ADMIN_UI: Products: [";
    std::vector<Product *> products = db.getProducts();
    int num_products = products.size();
    for (int i = 0; i<num_products - 1; i++){
        Product *product = products[i];
        os<<"("<<product->name<<", "<<product->price<<"), ";
    }
    Product *product = products[num_products - 1];
    os<<"("<<product->name<<", "<<product->price<<")";
    os<<"]\n";
}
