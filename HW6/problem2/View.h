//
// Created by mun on 20. 12. 11..
//

#ifndef PROBLEM2_VIEW_H
#define PROBLEM2_VIEW_H
#include <iostream>
class View{
    std::istream& userInput;
    std::ostream& printStream;
    View(std::istream& is, std::ostream& os);
    std::string getUserInput(std::string prompt);
};

#endif //PROBLEM2_VIEW_H
