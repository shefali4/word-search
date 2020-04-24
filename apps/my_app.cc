// Copyright (c) 2020 Shefali Sharma. All rights reserved.

#include "my_app.h"
#include <cinder/gl/gl.h>
#include <cinder/Text.h>
#include "cinder/Rect.h"
#include <list>
#include <cinder/app/App.h>
#include <SFML/Window.hpp>

namespace myapp {

using cinder::Color;
const char kDbPath[] = "game.db";
using cinder::ColorA;
using cinder::app::KeyEvent;
using cinder::TextBox;
using namespace std;
mylibrary::Player player = {"shefali", 3, 20.0};
string build_word;
int type_x_loc = 300;
const char kNormalFont[] = "Arial";
int count = 0;
int itr_count = 0;
int words_left;
string words[] = {"apple", "orange", "banana", "grape", "kiwi", "melon",
                  "pear", "coconut", "cherry", "avacado", "peach"};

std::list<string> word_bank;
std::list<string> already_answered;
double duration = .99;



WordSearch::WordSearch()
  :
    state_{GameState::kPlaying} {}

void WordSearch::setup() {
  word_bank.clear();
  timer.start(0);
}

void WordSearch::update() {
  KeyEvent event;
  keyDown(event);
  /*cinder::gl::color(1,0,0);
  const string timer_text = std::to_string(std::trunc(timer.getSeconds()));
  sf::sleep(sf::milliseconds(950));
  cinder::gl::color(1,1,0);
  cinder::gl::drawSolidCircle({50,40}, 40.0f);
  PrintText(timer_text, {50,40});
*/
  //leaderboard_.AddScoreToLeaderBoard(player);
}

void WordSearch::draw() {
  DisplayWordsFound();
  if (count == 0) {
    InitializeEmpty();
    InsertWords();
    RandomLetters();
    DrawSquares();
    DrawGrid();
    DisplayFilledGrid();
    DisplayCheat();
    count++;
  }

  DisplayWordCounter();

}

void myapp::WordSearch::PrintText(const std::string& text,
                           const glm::vec2& loc) {
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 18))
      .size({400, 50})
      .color(Color::white())
      .backgroundColor(ColorA(1, 0.988, 0.839, 0))
      .text(text);
  const auto text_size = box.getSize();
  const cinder::vec2 text_loc =
      {loc.x - text_size.x / 2, loc.y - text_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, text_loc);
}

void myapp::WordSearch::InitializeEmpty() {

  int loc_x = 288;
  int loc_y = 110;
  cinder::gl::color(Color::black());
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      cinder::vec2 loc = {loc_x, loc_y};
      map[i][j] = "_";
      valid_letter[i][j] = false;
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }
  for (int i = 0; i < words->size(); i++) {
    word_bank.push_back(words[i]);
  }
}

void myapp::WordSearch::DisplayWordsFound() {
  int loc_y_words = 130;
  if (already_answered.size() > itr_count) {
    for (auto itr = already_answered.begin(); itr != already_answered.end(); ++itr) {
      loc_y_words += 35;
      PrintText(*itr, {140, loc_y_words});

    }
    itr_count++;
  }

}

void myapp::WordSearch::InsertWords() {
  int row, col;
  for (int j = 0; j < words->size(); j++) {
    //if word length is even, place word vertically
    if (words[j].length() % 2 == 0) {
      row = rand() % 2;
      col = rand() % 20;
      for (int even = 0; even < words[j].length(); even++) {
        if (map[row][col] == "_") {
          PerWord(even, row, col, j);
          valid_letter[row][col] = true;
          row++;
        } else {

          word_bank.remove(words[j]);
          break;
        }
      }
    }

    //if word length is odd, place word horizontally
    if (words[j].length() % 2 != 0) {
      row = rand() % 20;
      col = rand() % 2;
      for (int odd = 0; odd < words[j].length(); odd++) {
        if (map[row][col] == "_") {
          PerWord(odd, row, col, j);
          valid_letter[row][col] = true;
          col++;
        } else {

          word_bank.remove(words[j]);
          break;
        }
      }
    }
  }
  words_left = word_bank.size();
}

//Goes through word and places letters horizontally/vertically depending on
//changing row and col values
void myapp::WordSearch::PerWord(int index, int row, int col, int j) {
  string word = words[j];
  char each_char = toupper(word.at(index));
  string string_char(1,each_char);
  map[row][col] = string_char;
}

//Chooses random letters excluding vowels
void myapp::WordSearch::RandomLetters() {
  char letters[] = "bcdfghjklmnpqrstvwxz";
  srand (time(nullptr));
  char random_char;
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 20; col++) {
      if (map[row][col] == "_") {
        random_char = toupper(letters[rand() % 20]);
        map[row][col] = random_char;
      }
    }
  }
}

void myapp::WordSearch::DisplayFilledGrid() {
  int loc_x = 288;
  int loc_y = 110;
  cinder::vec2 loc_words_found = {140, 130};
  PrintText("Words Found:", loc_words_found);
  cinder::vec2 loc_words_left = {700, 66};
  PrintText("Words Left: ", loc_words_left);
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 20; col++) {
      cinder::vec2 loc = {loc_x, loc_y};
      PrintText(map[row][col], loc);
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }
}

//Draws grid patterns using rectangle outlines
void myapp::WordSearch::DrawGrid() {
  cinder::gl::lineWidth(100);
  int increment = 25;
  int left = 275;
  int right = 300;
  int up = 85;
  int down = 110;
  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::drawSolidRect( cinder::Rectf
                                        ( 0,0,800,800));
  cinder::gl::color(0.184, 0.901, 0.933);
  cinder::gl::drawSolidRoundedRect( cinder::Rectf
                                        ( 271,80,790,575), 20);
  cinder::gl::color(Color::black());
}

//Displays Cheat box and text box
void myapp::WordSearch::DisplayCheat() {
  cinder::gl::color(1,0,0);
  cinder::gl::drawStrokedRect( cinder::Rectf
  ( 60,500,90,530),5);
  PrintText("HINT", {140, 530});
  cinder::gl::color(Color::black());

}


void myapp::WordSearch::keyDown( cinder::app::KeyEvent event ) {
  if (event.isAltDown()) {
    type_x_loc = 300;
    cinder::gl::color(0.988, 0.980, 0.835);
    cinder::gl::drawSolidRect(cinder::Rectf
                                  (80, 600, 800, 800));
    if (InWordBank(build_word) && AlreadyAnswered(build_word)) {
      cinder::gl::color(Color::black());
      PrintText("ALREADY ANSWERED!", {600, 700});
    } else if (InWordBank(build_word) && !AlreadyAnswered(build_word)){
      cinder::gl::color(Color::black());
      PrintText("CORRECT!", {600, 700});
      already_answered.push_back(build_word);
    } else {
      cinder::gl::color(Color::black());
      PrintText("INCORRECT! TRY AGAIN!", {600, 700});
    }
    build_word.clear();

  } else if (event.getChar()) {
    cinder::gl::color(0.988, 0.980, 0.835);
    cinder::gl::drawSolidRect( cinder::Rectf
                                   ( 480,600,800,800) );
    cinder::gl::color(Color::black());
    string this_char (1, event.getChar());
    build_word.append(this_char);
    cinder::vec2 text_loc = {type_x_loc, 700};
    type_x_loc += 9;
    PrintText(this_char, text_loc);
  }

  //If shift is pressed, mark cheat box red
  if (event.isShiftDown()) {
    DrawSquares();
    cinder::gl::color(1 ,0,0);
    cinder::gl::drawSolidRect( cinder::Rectf
    ( 60,500,90,530));
  }
}

void myapp::WordSearch::keyUp(cinder::app::KeyEvent event) {

  //If shift is not being pressed, keep cheat box unmarked
  if (!event.isShiftDown()) {
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawStrokedRect(cinder::Rectf
                                    (60, 500, 90, 530), 5);
    cinder::gl::color(0.988, 0.980, 0.835);
    cinder::gl::drawSolidRect(cinder::Rectf
                                  (62, 502, 88, 528));
  }

}

bool myapp::WordSearch::AlreadyAnswered(string build_word) {
  bool found = false;
  for (auto aa = already_answered.begin(); aa != already_answered.end();++aa) {
    if (*aa == build_word) {
      found = true;
      return found;
    }
  }
  return found;
}

bool myapp::WordSearch::InWordBank(string build_word) {
  bool found = false;
  for (auto itr = word_bank.begin(); itr != word_bank.end(); ++itr) {
    if (*itr == build_word) {
      found = true;
      return found;
    }
  }
  return found;
}

bool myapp::WordSearch::DisplayWordCounter() {
  cinder::gl::color(Color::black());
  cinder::vec2 loc_words = {760, 66};
  PrintText(std::to_string(words_left), loc_words);
}

void myapp::WordSearch::DrawSquares() {
  int left_start = 275;
  int right_start = 296;
  int bottom_start = 106;
  int top_start = 85;
  int increment = 25;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      if (valid_letter[i][j]) {
        cinder::gl::color(0, 1, 0);
        cinder::gl::drawSolidRect(cinder::Rectf(left_start,
                                                top_start,
                                                right_start,
                                                bottom_start));
      }
      left_start += increment;
      right_start += increment;

    }
    left_start = 274;
    right_start = 298;
    top_start += increment;
    bottom_start += increment;
  }
}
}// namespace myapp
