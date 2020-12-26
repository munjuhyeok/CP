//
// Created by mun on 20. 12. 12..
//


#include "BackEnd.h"

std::vector<std::string> split(std::string);
int check_occurrence(Post post,std::unordered_set<std::string> keywords);

const std::string BackEnd::serverStorageDir = SERVER_STORAGE_DIR;
const std:: string BackEnd::formatter = "%Y/%m/%d %H:%M:%S";

const std::string &BackEnd::getServerStorageDir() {
    return serverStorageDir;
}

bool BackEnd::auth(std::string id, std::string passwd) {
    std::ifstream file(serverStorageDir+id+"/password.txt");
    std::string correctPasswd;
    if(file){
        getline(file,correctPasswd);
        if(passwd == correctPasswd){
            userId = id;
            return true;
        }
    }
    return false;
}

void BackEnd::post(Post* post) {
    std::string postPath = serverStorageDir + userId + "/post/";
    int postId = -1;

    for(const auto &user : std::filesystem::directory_iterator(serverStorageDir)) {
        std::string postPath = user.path();
        postPath += "/post/";
        for (const auto &postFile : std::filesystem::directory_iterator(postPath)) {
            std::string temp = postFile.path().filename();
            size_t pos = temp.find(".");
            temp = temp.substr(0, pos);
            postId = std::max(postId, stoi(temp));
        }
    }
    postId++;

    std::string date = post->getDate();
    std::string title = post->getTitle();
    std::string content = post->getContent();
    std::ofstream post_file(postPath + std::to_string(postId) + ".txt");
    post_file<<date+"\n";
    post_file<<title+"\n\n";
    post_file<<content;
    post_file.close();
}


std::vector<Post> BackEnd::recommend() {
    struct compare{
        bool operator()(Post& post1, Post& post2){
            std::string time1, time2;
            time1 = post1.getDate();
            time2 = post2.getDate();
//            time_t time1, time2;
//            time1 = Post::parseDateTimeString(post1.getDate(),BackEnd::formatter);
//            time2 = Post::parseDateTimeString(post2.getDate(),BackEnd::formatter);
            return time1>time2;
        }
    };
    std::string friends = serverStorageDir + userId + "/friend.txt";
    std::ifstream friendFile(friends);
    std::priority_queue<Post,std::vector<Post>,compare> recommended;
    std::string friendId;
    while (getline(friendFile,friendId)){
        std::string postPath = serverStorageDir + friendId + "/post/";
        for(const auto &postFile : std::filesystem::directory_iterator(postPath)){
            std::string fileName = postFile.path();
            Post post = file_to_post(fileName);
            recommended.push(post);
            if(recommended.size() == num_recommend+1){
                recommended.pop();
            }
        }
    }
    std::vector<Post> v;
    while (!recommended.empty())
    {
        v.insert(v.begin(),recommended.top());
        recommended.pop();
    }
    return v;
}


std::vector<Post> BackEnd::search(std::unordered_set<std::string> keywords) {
    class compare{
    public:
        compare(std::unordered_set<std::string> keywords):keywords(keywords){};
        std::unordered_set<std::string> keywords;
        bool operator()(Post& post1,Post& post2){
            int occurrence1 = check_occurrence(post1,keywords);
            int occurrence2 = check_occurrence(post2,keywords);
            if(occurrence1 == occurrence2){

                std::string time1, time2;
                time1 = post1.getDate();
                time2 = post2.getDate();
//                time_t time1, time2;
//                time1 = Post::parseDateTimeString(post1.getDate(),BackEnd::formatter);
//                time2 = Post::parseDateTimeString(post2.getDate(),BackEnd::formatter);
                return time1>time2;
            }
            return occurrence1>occurrence2;
        }
    };
    std::priority_queue<Post,std::vector<Post>,compare> searched((compare(keywords)));
    for(const auto &user : std::filesystem::directory_iterator(serverStorageDir)) {
        std::string postPath = user.path();
        postPath += "/post/";
        for(const auto &postFile : std::filesystem::directory_iterator(postPath)){
            std::string fileName = postFile.path();
            Post post = file_to_post(fileName);
            int occurrence = check_occurrence(post,keywords);
            if(occurrence==0){
                continue;
            }
            searched.push(post);
            if(searched.size()==num_search+1){
                searched.pop();
            }
        }
    }
    std::vector<Post> v;
    while (!searched.empty())
    {
        v.insert(v.begin(),searched.top());
        searched.pop();
    }
    return v;
}

Post BackEnd::file_to_post(std::string fileName) {
    std::ifstream postStream(fileName);
    std::string str;
    std::string time;
    getline(postStream, time);
//    time_t time = Post::parseDateTimeString(str,formatter);
    std::string title;
    getline(postStream,title);
    size_t pos1 = fileName.rfind("/");
    size_t pos2 = fileName.find(".");
    std::string temp = fileName.substr(pos1+1,pos2);
    int id = stoi(temp);

    std::string content;
    getline(postStream,str); //remove first newline
//    getline(postStream,content); //first content line
    while(getline(postStream,str)){
        content+="\n"+str;
    }

    Post post(id,time,title,content);
    return post;
}

std::vector<std::string> split(std::string str){
    std::vector<std::string> keywords;
    std::istringstream ss(str);
    std::string keyword;
    while (ss >> keyword)
    {
        keywords.push_back(keyword);
    }
    return keywords;
}

int check_occurrence(Post post, std::unordered_set<std::string> keywords) {
    int occurrence = 0;
    std::vector<std::string> title_keywords = split(post.getTitle());
    std::vector<std::string> content_keywords = split(post.getContent());
    for(std::string keyword:keywords){
        occurrence += std::count(title_keywords.begin(),title_keywords.end(),keyword);
        occurrence += std::count(content_keywords.begin(),content_keywords.end(),keyword);
    }
    return occurrence;
}
