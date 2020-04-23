// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#include <mylibrary/example.h>
#include <string>
#include "player.h"

namespace mylibrary {

class LeaderBoard {
 public:

  // Creates a new leaderboard table if it doesn't already exist.
  explicit LeaderBoard(const std::string& db_path);

  LeaderBoard(const std::__1::basic_string<char,
                                           std::__1::char_traits<char>,
                                           std::__1::allocator<
                                               char>> &db_path);
// Adds a player to the leaderboard.
  void AddScoreToLeaderBoard(const mylibrary::Player &player);

  // Returns a list of the players with the highest scores, in decreasing order.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveHighScores(const size_t limit);

  // Returns a list of the players with the highest scores, in decreasing order,
  // that have the same `name` as the input player name.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveHighScores(const Player&, const size_t limit);

 private:
  sqlite::database db_;

};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
