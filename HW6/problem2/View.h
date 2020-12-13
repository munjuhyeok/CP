//
// Created by mun on 20. 12. 11..
//

#ifndef PROBLEM2_VIEW_H
#define PROBLEM2_VIEW_H
#include <iostream>
#include <utility>
#include "Post.h"

class View{
public:
    std::istream& is;
    std::ostream& os;
    View(std::istream& is, std::ostream& os);
    virtual std::string getUserInput(std::string prompt);
};

class PostView: public View{
public:
    PostView(std::istream& is, std::ostream& os);
    std::pair<std::string,std::string> getPost(std::string prompt);
};

class AuthView:public View{
public:
    AuthView(std::istream& is, std::ostream& os);
    std::string getUserInput(std::string prompt) override;
};

#endif //PROBLEM2_VIEW_H
