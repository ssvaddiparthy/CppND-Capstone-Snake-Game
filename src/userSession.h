#ifndef userSession
#define userSession

#include <string>

class UserSession {
    private:
        std::string userName;
        int score;
    public:
        UserSession(std::string);
        int getScore();
        void setScore(int score);
        std::string getUserName();
};

#endif
