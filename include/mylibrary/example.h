// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#include <mylibrary/example.h>
#include <string>
#include "player.h"
#include <sqlite_modern_cpp.h>

namespace mylibrary {

class LeaderBoard {
 public:

  /**
   * Creates a new leaderboard table if it doesn't already exist.
   */
  explicit LeaderBoard(const std::string& db_path);

  /**
   * // Adds a player to the leaderboard.
   * @param player
   */
  void AddScoreToLeaderBoard(const mylibrary::Player &player);

  /**
   * Returns a list of the players with the highest scores, in decreasing
   * order.
   * @param limit
   * @return The size of the list should be no greater than `limit`.
   */
  std::vector<Player> RetrieveHighScores(const size_t limit);

  /**
   * Returns a list of the players with the highest scores, in decreasing order
   * @param limit The size of the list should be no greater than `limit`.
   * @return
   */
  std::vector<Player> RetrieveHighScores(const Player&, const size_t limit);
  sqlite::database db_;
};
}  // namespace mylibrary
#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
