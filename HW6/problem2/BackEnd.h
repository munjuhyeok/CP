//
// Created by mun on 20. 12. 12..
//

#ifndef PROBLEM2_BACKEND_H
#define PROBLEM2_BACKEND_H
#include "config.h"
#include <iostream>
#include <fstream>
#include "Post.h"
#include <filesystem>
#include <string>
#include <vector>
#define num_recommend 10

class BackEnd {
private:
    const static std::string serverStorageDir;
    const static std::string formatter;
    std::string userId;
public:
    static const std::string &getServerStorageDir();
    bool auth(std::string id, std::string passwd);
    void post(Post* post);
    std::vector<Post*> recommend();
};


#endif //PROBLEM2_BACKEND_H
