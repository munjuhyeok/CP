#ifndef PROBLEM2_APP_H
#define PROBLEM2_APP_H
#include "View.h"
#include "FrontEnd.h"

class App {
public:
    App(std::istream& is, std::ostream& os);
    void run();
    PostView* postView;
    AuthView* authView;
    View* mainView;
private:
    std::istream& is;
    std::ostream& os;
    FrontEnd* frontEnd;
    bool query(std::string command);
    static std::string parseInstruction(std::string command);
    void post();
    void search(std::string command);
    void recommend();
};

#endif //PROBLEM2_APP_H
