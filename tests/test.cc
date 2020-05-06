// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>


using myapp::WordSearch;


TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}



/*
TEST_CASE("Already Answered", "[already-answered]") {
  std::list<std::string> file_words;
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

*/