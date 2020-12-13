//
// Created by mun on 20. 12. 12..
//

#include "BackEnd.h"

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
    for(const auto &postFile : std::filesystem::directory_iterator(postPath)){
        std::string temp = postFile.path().filename();
        size_t pos = temp.find(".");
        temp = temp.substr(0,pos);
        postId = std::max(postId,stoi(temp));
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

std::vector<Post*> BackEnd::recommend() {
    std::string friends = serverStorageDir + userId + "/friend.txt";
    std::ifstream friendFile(friends);
    std::vector<Post*> recommended;
    std::vector<time_t> times;
    std::string friendId;
    while (getline(friendFile,friendId)){
        std::string postPath = serverStorageDir + friendId + "/post/";
        int num_recommended;
        for(const auto &postFile : std::filesystem::directory_iterator(postPath)){
            num_recommended = recommended.size();
            std::string post = postFile.path();
            std::ifstream postStream(post);
            std::string str;
            getline(postStream, str);
            time_t time = Post::parseDateTimeString(str,formatter);
            for(int i=0;i<num_recommend;i++){
                if(num_recommended ==i ||difftime(time,times[i])>0){
                    std::string title;
                    getline(postStream,title);
                    std::string temp = postFile.path().filename();
                    size_t pos = temp.find(".");
                    temp = temp.substr(0,pos);
                    int id = stoi(temp);
                    std::string content;
                    getline(postStream,str); //remove first newline
                    while(getline(postStream,str)){
                        content+="\n"+str;
                    }
                    recommended.insert(recommended.begin()+i, new Post(id, time,title,content));
                    times.insert(times.begin()+i, time);
                    break;
                }
            }
            if(recommended.size() == num_recommend+1){
                recommended.pop_back();
                times.pop_back();
            }
        }
    }
    return recommended;
}
