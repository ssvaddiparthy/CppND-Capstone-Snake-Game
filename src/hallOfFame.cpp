#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>


#include "hallOfFame.h"

HallOfFame::HallOfFame()
{
    std::ifstream fileInp;
    fileInp.open("../hall_of_fame.txt");

    std::string line;
    while (fileInp)
    {
        getline(fileInp, line);
        std::vector<std::string> parts;
        std::string buffer;

        if(line.size() == 0)
        {
            return;
        }

        for(std::string::size_type i = 0; i < line.size(); i++)
        {
            if(line[i] == ',')
            {
                parts.push_back(buffer);
                buffer = "";
            }
            else
            {
                buffer.push_back(line[i]);
            }
            
        }
        
        struct Record* rec = new Record();
        rec->rank = (int) std::strtol(parts[0].c_str(), nullptr, 10);
        rec->name = parts[1];
        rec->score = (int) std::strtol(parts[2].c_str(), nullptr, 10);
        
        currentWinners.push_back(rec);
    }
    fileInp.close();
};

HallOfFame::~HallOfFame()
{
    for(auto it = currentWinners.begin(); it != currentWinners.end(); it++)
    {
        delete *it;
    }
}

// copy constructor
HallOfFame::HallOfFame(const HallOfFame &obj)
{
    for (auto it = obj.currentWinners.begin(); it != obj.currentWinners.end(); it++)
    {
        struct Record* rec = new Record();
        rec->rank = (*it)->rank;
        rec->name = (*it)->name;
        rec->score = (*it)->score;
        currentWinners.push_back(rec);
    }
    
};

// move constructor
HallOfFame::HallOfFame(HallOfFame&& obj)
{
    for (auto it = obj.currentWinners.begin(); it != obj.currentWinners.end(); it++)
    {
        currentWinners.push_back(*it);
        obj.currentWinners.erase(it);
    }
};

// copy operator
HallOfFame& HallOfFame::operator=(const HallOfFame& obj)
{
    for (auto it = obj.currentWinners.begin(); it != obj.currentWinners.end(); it++)
    {
        struct Record* rec = new Record();
        rec->rank = (*it)->rank;
        rec->name = (*it)->name;
        rec->score = (*it)->score;
        currentWinners.push_back(rec);
    }
    return *this;
};

// move operator
HallOfFame& HallOfFame::operator=(HallOfFame&& obj)
{
    if (this != &obj) 
    {
        for (auto it = obj.currentWinners.begin(); it != obj.currentWinners.end(); it++)
        {
            currentWinners.push_back(*it);
            obj.currentWinners.erase(it);
        }
    }
    return *this;
};

int HallOfFame::addRecord(int score, std::string name)
{
    struct Record *temp = new Record();
    temp->name = name;
    temp->score = score;
    temp->rank = -1;

    currentWinners.push_back(temp);
    std::sort(currentWinners.begin(), currentWinners.end(), [](struct Record* rec1, struct Record* rec2) -> bool {return (rec1->score > rec2->score);});
    
    int cur_rank = 1;
    int prev_score = currentWinners[0]->score;
    for (auto it = currentWinners.begin(); it != currentWinners.end(); it++)
    {
        if(prev_score > (*it)->score)
        {
            cur_rank++;
            prev_score = (*it)->score;
        }
        (*it)->rank = cur_rank;
        // std::cout << "Name " << (*it)->name << "Assigned rank " << (*it)->rank << " with score " <<  (*it)->score << "\n";
    }
    std::cout << currentWinners.back()->rank << "\t" << currentWinners.back()->score << "\t" << currentWinners.back()->name << "\n";
            
    if (currentWinners.back()->rank >= 4)
    {
        currentWinners.pop_back();
        if(currentWinners.back() == temp)
        {
            return -1;
        }
    }
    
    for(auto it = currentWinners.begin(); it < currentWinners.end(); it++)
    {
        if(*it == temp)
        {
            return (*it)->rank;
        }
    }
    return -1;
};

void HallOfFame::saveRecords()
{
    std::ofstream fameSaver;
    fameSaver.open("../hall_of_fame.txt");
    for(auto it = currentWinners.begin(); it != currentWinners.end(); it++)
    {
        fameSaver << (*it)->rank << "," << (*it)->name << "," << (*it)->score << ",\n"; 
    }
    fameSaver.close();


};

void HallOfFame::showRecords()
{
    for(auto it = currentWinners.begin(); it != currentWinners.end(); it++)
    {
        std::cout << (*it)->rank << "\t" << (*it)->name << "\t" << (*it)->score << "\n"; 
    }
}