//
// Created by mun on 20. 12. 11..
//

#ifndef PROBLEM2_USER_H
#define PROBLEM2_USER_H
#include <iostream>
class User{
public:
    std::string id;
    User(std::string id, std::string password);
private:
    std::string password;
};
#endif //PROBLEM2_USER_H
