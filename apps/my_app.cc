// Copyright (c) 2020 Shefali Sharma. All rights reserved.

#include "my_app.h"
#include <cinder/gl/gl.h>
#include <cinder/Text.h>
#include "cinder/Rect.h"
#include <list>
#include <cinder/app/App.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::TextBox;
using namespace std;
string build_word;

const char kNormalFont[] = "Arial";
using cinder::Color;
using cinder::ColorA;
int count = 0;
string words[] = {"apple", "orange", "banana", "grape", "kiwi", "melon",
                  "pea", "asdfasdfasdfasdfasdfasdf"};
list<string> word_bank = {};
string typed_words[] = {};





WordSearch::WordSearch() {


}

void WordSearch::setup() {
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
  keyUp(event);
  keyDown(event);



}

void WordSearch::draw() {

  if (count == 0) {

    Cheat();
    DrawGrid();
    InitializeEmpty();
    InsertWords();
    RandomLetters();
    WordsFound();
    Display();
    DrawSquares();
    count++;
  }



}

//void WordSearch::keyDown(KeyEvent event) { }

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
  for (int i = 0; i < words->size(); i++) {
    word_bank.push_front(words[i]);
  }
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

void WordSearch::WordsFound() {
  int loc_y = 90;
  cinder::vec2 loc = {135, loc_y};
  PrintText("Words Found:", loc);
  for (int i = 0; i < words->size(); i++) {
    loc_y += 50;
    PrintText(words[i] + "\n", {135, loc_y});

  }
}



void WordSearch::InsertWords() {
  int row, col;

  for (int j = 0; j < words->size(); j++) {
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

void WordSearch::PerWord(int c, int row, int col, int j) {
  string word = words[j];
  char a = word.at(c);
  string s(1,a);
  map[row][col] = s;
}

void WordSearch::Display() {
  int loc_x = 288;
  int loc_y = 110;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      cinder::vec2 loc = {loc_x, loc_y};
      PrintText(map[i][j], loc);
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }
}

void WordSearch::RandomLetters() {
  srand (time(NULL));
  char random_char;
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 20; col++) {
      if (map[row][col] == "_") {
        random_char = 'a' + (rand() % 26);
        map[row][col] = random_char;
      }
    }
  }
}

void WordSearch::DrawGrid() {
  cinder::gl::lineWidth(100);
  int increment = 25;
  int left = 275;
  int right = 300;
  int up = 85;
  int down = 110;
  for (int i = 0; i < 20; i++) {
    cinder::gl::drawStrokedRect(cinder::Rectf(right,85,left,585));
    right+=increment;
    left+= increment;

  }

  cinder::gl::ScopedColor(1, 0,0);
  for (int i = 0; i < 20; i++) {
    cinder::gl::drawStrokedRect(cinder::Rectf(275, up, 775, down));
    up += increment;
    down += increment;
  }
}

void WordSearch::DrawSquares() {
/*  sf::RenderWindow window;
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 20; col++) {

      sf::RectangleShape rectangle(sf::Vector2f(120, 50));
      rectangle.setSize(sf::Vector2f(100, 100));
      window.draw(rectangle);
      window.display();

    }
  }
*/


}

void WordSearch::Cheat() {

  cinder::gl::color(1,0,0);
  cinder::gl::drawStrokedRect( cinder::Rectf( 80,500,130,550) );

}

void WordSearch::keyDown( cinder::app::KeyEvent event ) {
  string this_char (1, event.getChar());
  build_word.append(this_char);
  cinder::vec2 loc = {135, 135};
  int count = 0;
  if (event.getChar() == '!') {
    for (int i = 0; i < words->length(); i++) {
      for (int j = 0; j < typed_words[0].length(); j++) {
        if (words[count] + '!' == this_char) {
          PrintText("Worked", loc);
        }
      }
    }
  }
}

void WordSearch::keyUp( cinder::app::KeyEvent event ) {
  /*if( event.getChar() == 'a' ) {

    cinder::gl::color(0,1,0);
    cinder::gl::drawStrokedRect( cinder::Rectf( 80,500,130,550) );
  }*/
}



//

}  // namespace myapp

