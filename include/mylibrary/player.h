//
// Created by Shefali Sharma on 4/23/20.
//

#ifndef FINALPROJECT_INCLUDE_MYLIBRARY_PLAYER_H_
#define FINALPROJECT_INCLUDE_MYLIBRARY_PLAYER_H_

using namespace std;
namespace mylibrary {



struct Player {
  Player(const std::string& name, size_t score, double time) : name(name),
                                                               score(score), time(time) {}
  std::string name;
  size_t score;
  double time;
};

}  // namespace snake

#endif //FINALPROJECT_INCLUDE_MYLIBRARY_PLAYER_H_
