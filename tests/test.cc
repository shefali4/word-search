// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN


#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include "../apps/display.h"
#include "../apps/hint.h"
#include "../apps/my_app.h"
#include <list>
#include <string>

using myapp::WordSearch;
std::ifstream invalid_path("data/empty.spf");
std::ifstream valid_path("data/puzzle.spf");


TEST_CASE("Add to List", "[add-to-list]") {
  std::list<std::string> file_words;
  SECTION("Size") {
    file_words.push_back("APPLE");
    file_words.push_back("KIWI");
    file_words.push_back("BANANA");
    file_words.push_back("ORANGE");
    REQUIRE(file_words.size() == 4);
  }

  SECTION("Front") {
    file_words.push_back("APPLE");
    file_words.push_back("KIWI");
    file_words.push_back("BANANA");
    file_words.push_back("ORANGE");
    REQUIRE(file_words.front() == "APPLE");
  }
}

TEST_CASE("Answered Answered", "[already-answered]") {
  std::list<std::string> file_words;
  file_words.push_back("APPLE");
  file_words.push_back("KIWI");
  file_words.push_back("BANANA");
  file_words.push_back("ORANGE");

  SECTION("Has Been Answered") {
    std::string word = "APPLE";
    bool in_list = false;
    for (auto &answer : file_words) {
      if (answer == word) {
        in_list = true;
        break;
      }
    }
    REQUIRE(in_list);
  }

  SECTION("Has Not Been Answered") {
    std::string word = "PEACH";
    bool in_list = false;
    for (auto &answer : file_words) {
      if (answer == word) {
        in_list = true;
        break;
      }
    }
    REQUIRE(!in_list);
  }
}

TEST_CASE("In Word Bank", "[in-word-bank]") {
  std::list<std::string> word_bank;
  word_bank.push_back("APPLE");
  word_bank.push_back("KIWI");
  word_bank.push_back("BANANA");
  word_bank.push_back("ORANGE");

  SECTION("In Word Bank") {
    std::string word = "APPLE";
    bool in_list = false;
    for (auto &answer : word_bank) {
      if (answer == word) {
        in_list = true;
        break;
      }
    }
    REQUIRE(in_list);
  }

  SECTION("Not In Word Bank") {
    std::string word = "PEACH";
    bool in_list = false;
    for (auto &answer : word_bank) {
      if (answer == word) {
        in_list = true;
        break;
      }
    }
    REQUIRE(!in_list);
  }
}

TEST_CASE("Invalid File", "[invalid-file]") {

  SECTION("Invalid Path") {
    bool valid = false;
    if (invalid_path.fail()) {
      valid = true;
    }
    REQUIRE(valid == true);
  }

  SECTION("Valid Path") {
    bool valid = false;
    if (valid_path.fail()) {
      valid = true;
    }
    REQUIRE(valid == true);
  }
}
