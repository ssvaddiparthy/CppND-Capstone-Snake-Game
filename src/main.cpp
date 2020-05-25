#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "userSession.h"
#include "hallOfFame.h" 

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  HallOfFame hf = HallOfFame();
  UserSession* curSession = game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  int rank = hf.addRecord(curSession->getScore(), curSession->getUserName());
  std::cout << "User: " << curSession->getUserName() << "\tScore: " << curSession->getScore() << "\n";
  if(rank != -1)
  {
    std::cout << "Congrats you have made it to the hall of fame with rank: " << rank << "\n";
    hf.showRecords();
  }
  hf.saveRecords();
  return 0;
}