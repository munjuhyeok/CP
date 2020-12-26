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
#include <queue>
#include <unordered_set>
#include <algorithm>

#define num_recommend 10
#define num_search 10

//class compare_search{
//public:
//    static std::unordered_set<std::string> keywords;
//    bool operator()(Post& post1, Post& post2){
//        int occurrence1 = check_occurrence(post1,keywords);
//        int occurrence2 = check_occurrence(post2,keywords);
//        return occurrence1>occurrence2;
//    }
//};

class BackEnd {
private:
    const static std::string serverStorageDir;
    const static std::string formatter;
    std::string userId;
    static Post file_to_post(std::string fileName);
//    static std::vector<std::string> split(std::string);
//    static int check_occurrence(Post post,std::unordered_set<std::string> keywords);
    std::unordered_set<std::string> keywords;
public:
    static const std::string &getServerStorageDir();
    bool auth(std::string id, std::string passwd);
    void post(Post* post);
    std::vector<Post> recommend();
    std::vector<Post> search(std::unordered_set<std::string>);
};


#endif //PROBLEM2_BACKEND_H
