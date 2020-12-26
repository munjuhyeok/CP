//
// Created by mun on 20. 12. 11..
//

#include "Post.h"


const char* const Post::formatter = "%Y/%m/%d %H:%M:%S";
void Post::setId(int id) {
    Post::id = id;
}


Post::Post(std::string title, std::string content):Post(ID_NOT_INITIATED, getDate(*(new time_t(time(0)))),title,content){}

Post::Post(int id, std::string dateTime, std::string title, std::string content) :id(id),dateTime(dateTime),title(title),content(content){}

std::string Post::getSummary() {
    std::stringstream ss;
    ss<<"id: "<<id<<", created at: "<<dateTime<<", title: "<<title;
    return ss.str();
}



const std::string &Post::getTitle() const {
    return title;
}

const std::string &Post::getContent() const {
    return content;
}

time_t Post::parseDateTimeString(std::string dateString, std::string dateTimeFormatter) {
    struct tm* time = localtime(new time_t(0));
    strptime(dateString.c_str(),dateTimeFormatter.c_str(),time);

    return mktime(time);

}

std::string Post::getDate(time_t dateTime) const{
    char date[80];
    strftime(date,80,formatter,localtime(&dateTime));
    return date;
}


std::string Post::getDate() const{
    return dateTime;
}

std::ostream& operator<<(std::ostream& os, const Post& post){
    return
    os<<"-----------------------------------\nid: "
    <<post.id<<"\ncreated at: "<<post.dateTime
    <<"\ntitle: "
    <<post.title
    <<"\ncontent:"
    <<post.content;
};