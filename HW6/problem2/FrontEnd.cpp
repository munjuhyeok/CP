//
// Created by mun on 20. 12. 12..
//

#include "FrontEnd.h"

FrontEnd::FrontEnd(std::ostream &os, BackEnd* backEnd):printStream(os), backEnd(backEnd){
}

bool FrontEnd::auth(std::string authInfo) {
    std::string delimiter = "\n";
    size_t pos = authInfo.find(delimiter);
    std::string id = authInfo.substr(0,pos);
    std::string passwd = authInfo.substr(pos+delimiter.length(),std::string::npos);
    if(backEnd->auth(id, passwd)){
        user = new User(id, passwd);
        return true;
    }
    return false;
}

User *FrontEnd::getUser() const {
    return user;
}

void FrontEnd::post(std::pair<std::string, std::string> titleContentPair) {
    std::string title = titleContentPair.first;
    std::string content = titleContentPair.second;
    backEnd->post(new Post(title, content));
}

void FrontEnd::recommend() {
    std::vector<Post*> recommended = backEnd->recommend();
    for(Post* post:recommended){
        printStream<<*post;
        printStream<<std::endl<< "-----------------------------------" << std::endl;
    }
}
