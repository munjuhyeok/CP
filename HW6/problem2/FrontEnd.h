//
// Created by mun on 20. 12. 12..
//

#ifndef PROBLEM2_FRONTEND_H
#define PROBLEM2_FRONTEND_H
#include <iostream>
#include "BackEnd.h"
#include "User.h"
#include <vector>

class FrontEnd {
private:
    std::ostream& printStream;
    BackEnd* backEnd;
    User* user;
public:
    User *getUser() const;

public:
    FrontEnd(std::ostream& os, BackEnd* backEnd);
    bool auth(std::string authInfo);
    void post(std::pair<std::string,std::string> titleContentPair);
    void recommend();
};


#endif //PROBLEM2_FRONTEND_H
