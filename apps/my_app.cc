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
using cinder::ColorA;
using cinder::app::KeyEvent;
using cinder::TextBox;
using namespace std;
string build_word;
int type_x_loc = 300;
const char kNormalFont[] = "Arial";
int count = 0;
string words[] = {"apple", "orange", "banana", "grape", "kiwi", "melon",
                  "pear", "coconut", "cherry", "avacado", "peach"};
list<string> word_bank = {};



WordSearch::WordSearch() {}

void WordSearch::setup() {
  word_bank.clear();
/*
  window.create(sf::VideoMode(800, 800), "SFML window");
  window.setFramerateLimit(60);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.setActive();
    window.display();
  }*/
}

void WordSearch::update() {
  KeyEvent event;
  keyDown(event);


}

void WordSearch::draw() {
  if (count == 0) {
    DrawGrid();
    InitializeEmpty();
    InsertWords();
    RandomLetters();
    DisplayFilledGrid();
    DisplayWordsFound();
    DisplayCheat();
    count++;
  }
}

void WordSearch::PrintText(const std::string& text,
                           const glm::vec2& loc) {
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 18))
      .size({400, 50})
      .color(Color::white())
      .backgroundColor(ColorA(1, 1, 0, 0))
      .text(text);

  const auto text_size = box.getSize();
  const cinder::vec2 text_loc =
      {loc.x - text_size.x / 2, loc.y - text_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, text_loc);
}

void WordSearch::InitializeEmpty() {
  int loc_x = 288;
  int loc_y = 110;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      cinder::vec2 loc = {loc_x, loc_y};
      map[i][j] = "_";
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }
}

void WordSearch::DisplayWordsFound() {
  int loc_y = 130;
  cinder::vec2 loc = {140, loc_y};
  PrintText("Words Found:", loc);
  for (int i = 0; i < words->size(); i++) {
    loc_y += 45;
    PrintText(words[i] + "\n", {140, loc_y});
  }
}

void WordSearch::InsertWords() {
  int row, col;
  for (int j = 0; j < words->size(); j++) {

    //if word length is even, place word vertically
    if (words[j].length() % 2 == 0) {
      row = rand() % 2;
      col = rand() % 20;
      for (int even = 0; even < words[j].length(); even++) {
        if (map[row][col] == "_") {
          PerWord(even, row, col, j);
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
          col++;
        } else {
          word_bank.remove(words[j]);
          break;
        }
      }
    }
  }

}

//Goes through word and places letters horizontally/vertically depending on
//changing row and col values
void WordSearch::PerWord(int index, int row, int col, int j) {
  string word = words[j];
  char each_char = word.at(index);
  string string_char(1,each_char);
  map[row][col] = string_char;
}

//Chooses random letters excluding vowels
void WordSearch::RandomLetters() {
  char letters[] = "bcdfghjklmnpqrstvwxz";
  srand (time(nullptr));
  char random_char;
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 20; col++) {
      if (map[row][col] == "_") {
        random_char = letters[rand() % 20];
        map[row][col] = random_char;
      }
    }
  }
}

void WordSearch::DisplayFilledGrid() {
  int loc_x = 288;
  int loc_y = 110;
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
void WordSearch::DrawGrid() {
  cinder::gl::lineWidth(100);
  int increment = 25;
  int left = 275;
  int right = 300;
  int up = 85;
  int down = 110;
  for (int i = 0; i < 20; i++) {

    //Horizontal rectangles
    cinder::gl::drawStrokedRect(cinder::Rectf
    (right,85,left,585), 2);
    right+=increment;
    left+= increment;
  }

  //Vertical rectangles
  cinder::gl::ScopedColor(1, 0,0);
  for (int i = 0; i < 20; i++) {
    cinder::gl::drawStrokedRect(cinder::Rectf
    (275, up, 775, down), 2);
    up += increment;
    down += increment;
  }
}

//Displays Cheat box and text box
void WordSearch::DisplayCheat() {
  cinder::gl::color(1,0,0);
  cinder::gl::drawStrokedRect( cinder::Rectf
  ( 60,500,90,530),5);
  PrintText("HINT", {140, 530});
  cinder::gl::color(Color::black());
}


void WordSearch::keyDown( cinder::app::KeyEvent event ) {

  if (event.getChar() == ' ') {
    type_x_loc = 300;
    cinder::gl::color(Color::black());
    cinder::gl::drawSolidRect( cinder::Rectf
                                   ( 80,600,800,750) );
    for (int i = 0; i < words->size(); i++) {
      if (words[i] == build_word) {
        cinder::gl::color(Color::white());
        PrintText("CORRECT!", {600, 700});
        word_bank.push_back(build_word);
        return;
      }
    }
    build_word.clear();
  } else if (event.getChar()) {
    cinder::gl::color(Color::white());
    string this_char (1, event.getChar());
    build_word.append(this_char);
    cinder::vec2 text_loc = {type_x_loc, 700};
    type_x_loc += 9;
    PrintText(this_char, text_loc);
  }

  //If shift is pressed, mark cheat box red
  if (event.isShiftDown()) {
    cinder::gl::color(1 ,0,0);
    cinder::gl::drawSolidRect( cinder::Rectf
    ( 60,500,90,530));
  }
}

void WordSearch::keyUp( cinder::app::KeyEvent event ) {

  //If shift is not being pressed, keep cheat box unmarked
  if (!event.isShiftDown()) {
    cinder::gl::color(1,0,0);
    cinder::gl::drawStrokedRect( cinder::Rectf
    ( 60,500,90,530),5);
    cinder::gl::color(Color::black());
    cinder::gl::drawSolidRect( cinder::Rectf
    ( 62,502,88,528));
  }
}
}  // namespace myapp
