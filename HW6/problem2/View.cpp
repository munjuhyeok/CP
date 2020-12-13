//
// Created by mun on 20. 12. 11..
//

#include "View.h"

View::View(std::istream &is, std::ostream &os): is(is), os(os){}

std::string View::getUserInput(std::string prompt) {
    os << prompt;
    std::string nextLine;
    getline(is, nextLine);
    return nextLine;
}

PostView::PostView(std::istream &is, std::ostream &os) : View(is, os) {}

std::pair<std::string, std::string> PostView::getPost(std::string prompt) {

    std::string title;
    std::string content;
    std::string entireContent = "";
    os << "-----------------------------------" << std::endl;
    os << prompt << std::endl;
    os << "* Title=" << std::endl;
    getline(is, title);
    os << "* Content" << std::endl;
    os << "> "<<std::endl;
    getline(is, content);
    entireContent += content + "\n";
    while(!(content == "")){
        os << "> " << std::endl;
        getline(is, content);
        entireContent += content + "\n";
    }
//    os << "-----------------------------------" << std::endl;
    return std::make_pair(title, entireContent);
}

AuthView::AuthView(std::istream &is, std::ostream &os) : View(is, os){}

std::string AuthView::getUserInput(std::string prompt) {
    std::string id, passwd;
    os << prompt;
    os << "id=" << std::endl;
    getline(is, id);
    os << "passwd=" << std::endl;
    getline(is, passwd);
    return id + "\n" + passwd;
}
