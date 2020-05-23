#include "userSession.h"
#include <string>

UserSession::UserSession(std::string userName): userName(userName){
    UserSession::score = 0;
};

int UserSession::getScore(){
    return UserSession::score;
};

void UserSession::setScore(int score){
    UserSession::score = score;
};

std::string UserSession::getUserName(){
    return UserSession::userName;
}