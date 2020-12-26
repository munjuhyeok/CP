#include <iostream>
#include "app.h"

App::App(std::istream& is, std::ostream& os): is(is), os(os){
    // TODO
    frontEnd = new FrontEnd(os, new BackEnd);
    postView = new PostView(is,os);
    authView = new AuthView(is,os);
    mainView = authView;
}

void App::run() {
    // TODO
    std::string command;
    std::string authInfo = authView->getUserInput("------ Authentication ------\n");
    if(frontEnd->auth(authInfo)){
        mainView = postView;
        do{
            command = postView->getUserInput(
                    "-----------------------------------\n" +
                    frontEnd->getUser()->id + "@sns.com\n" +
                    "post : Post contents\n" +
                    "recommend : recommend interesting posts\n" +
                    "search <keyword> : List post entries whose contents contain <keyword>\n" +
                    "exit : Terminate this program\n" +
                    "-----------------------------------\n" +
                    "Command=");
        } while (query(command));
    }else{
        os<<"Failed Authentication."<<std::endl;
    }
}

bool App::query(std::string command) {
    std::string instruction = parseInstruction(command);
    if(instruction == "exit"){
        return false;
    } else if(instruction == "post"){
        post();
    }else if(instruction == "search"){
        search(command);
    }else if(instruction =="recommend"){
        recommend();
    } else{
//        os<<"Illegal Command Format : "<<command<<std::endl;
    }
    return true;
}

std::string App::parseInstruction(std::string command) {
    size_t pos = command.find(" ");
    std::string instruction = command.substr(0,pos);
    return instruction;
}

void App::post() {
    frontEnd->post(postView->getPost("New Post"));
}

void App::search(std::string command) {
    frontEnd->search(command);
}

void App::recommend() {
    frontEnd->recommend();
}
