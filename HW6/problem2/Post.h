//
// Created by mun on 20. 12. 11..
//

#ifndef PROBLEM2_POST_H
#define PROBLEM2_POST_H
#include <iostream>
#include <time.h>
#include <sstream>

class Post{
private:
    const static char * const formatter;
    int id;
public:
    void setId(int id);

private:
    const static int ID_NOT_INITIATED = -1;
//    time_t dateTime;
    std::string dateTime, title, content;
public:
    const std::string &getTitle() const;

    const std::string &getContent() const;

public:
    Post(std::string title, std::string content);
    Post(int id, std::string dateTime, std::string title, std::string content);
    std::string getSummary();
    friend std::ostream& operator<<(std::ostream& os, const Post& post);
    static time_t parseDateTimeString(std::string dateString, std::string dateTimeFormatter);
    std::string getDate(time_t) const;
    std::string getDate() const;

};
#endif //PROBLEM2_POST_H
