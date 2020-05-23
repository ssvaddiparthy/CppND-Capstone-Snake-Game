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
        std::vector<struct Record> currentWiners;
    public:
        HallOfFame();
        void addRecord();
        void saveRecords();
};

#endif