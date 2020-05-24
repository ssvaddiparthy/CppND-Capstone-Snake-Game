#ifndef hallfOfFame
#define hallfOfFame

#include <string>
#include <vector>

struct Record{
    int rank;
    std::string name;
    int score;
};

class HallOfFame{
    private:
        std::vector<struct Record*> currentWinners;
    public:
        HallOfFame();
        ~HallOfFame();
        int addRecord(int score, std::string name);
        void saveRecords();
        void showRecords();
};

#endif