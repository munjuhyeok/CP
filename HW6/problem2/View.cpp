//
// Created by mun on 20. 12. 11..
//

#include "View.h"

View::View(std::istream &is, std::ostream &os): userInput(is), printStream(os){}

std::string View::getUserInput(std::string prompt) {
    printStream<<prompt;
    std::string nextLine;
    userInput>>nextLine;
}
