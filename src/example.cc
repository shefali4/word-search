// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/example.h>
#include <mylibrary/player.h>
#include <sqlite_modern_cpp.h>
#include <string>
#include <vector>

namespace mylibrary {

using std::string;
using std::vector;

LeaderBoard::LeaderBoard(const string &db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

//Adds name, score, and time data to leaderboard
void LeaderBoard::AddScoreToLeaderBoard(const Player &player) {
  db_ << "insert into leaderboard (name, score, time) values (?, ?, ?);"
      << player.name
      << player.score
      << player.time;
}

//Gets player data from row passed into parameters
vector<Player> GetPlayers(sqlite::database_binder *rows) {
  vector<Player> players;

  for (auto &&row : *rows) {
    string name = "";
    size_t score = 0;
    double time = 0.0;
    row >> name >> score >> time;
    Player player = {name, score, time};
    players.push_back(player);
  }

  return players;
}

//Retrieves high score among all players - ordered from high to low
vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
  auto rows = db_ << "select name, score, time from leaderboard order by score "
                     "desc limit ? offset 0;"
                  << limit;
  return GetPlayers(&rows);
}

//Retrieves high score for current player
vector<Player> LeaderBoard::RetrieveHighScores(const Player &player,
                                               const size_t limit) {
  auto rows = db_ << "select name, score, time from leaderboard where name = ? "
                     "order by score desc limit ? offset 0"
                  << player.name
                  << limit;

  return GetPlayers(&rows);
}

}  // namespace mylibrary