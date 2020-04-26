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
int col_count = 0;
int row_count = 0;
std::string col_string;
std::string row_string;
int col_index_found = -1;
int row_index_found = -1;
int row_loc;
int col_loc;
using cinder::TextBox;
using namespace std;
mylibrary::Player player = {"shefali", 3, 20.0};
string build_word;
int type_x_loc = 125;
const char kNormalFont[] = "Baskerville";
int count = 0;
int itr_count = 0;

int words_left;
string word_to_highlight;

string words[] = {"APPLE", "ORANGE", "BANANA", "GRAPE", "KIWI", "MELON",
                  "PEAR", "coconut", "cherry", "avacado", "peach"};
int words_size = words->size();

std::list<string> word_bank;
std::list<string> already_answered;

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
  HighlightWords();
  //leaderboard_.AddScoreToLeaderBoard(player);
}

void WordSearch::draw() {
  DisplayWordsFound();
  if (count == 0) {
    InitializeEmpty();
    InsertWords();
    DrawGrid();
    DrawUIBackground();
    RandomLetters();
    DisplayFilledGrid();
    DisplayCheat();
    DisplayTitle();
    count++;
  }
  DisplayWordCounter();
}

void myapp::WordSearch::PrintText(const std::string &text,
                                  const glm::vec2 &loc) {
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 20))
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
      answered_correctly[i][j] = false;
      loc_x += 27;
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
    for (auto itr = already_answered.begin(); itr != already_answered.end();
         ++itr) {
      loc_y_words += 35;
      PrintText(*itr, {140, loc_y_words});
    }
    itr_count++;
  }
}

void myapp::WordSearch::InsertWords() {
  int row, col;
  for (int j = 0; j < words_size; j++) {
    //if word length is even, place word vertically
    if (words[j].length() % 2 == 0) {
      row = rand() % 1;
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
      col = rand() % 1;
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
  string string_char(1, each_char);
  map[row][col] = string_char;
}

//Chooses random letters excluding vowels
void myapp::WordSearch::RandomLetters() {
  char letters[] = "bcdfghjklmnpqrstvwxz";
  srand(time(nullptr));
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
  cinder::vec2 loc_words_left = {110, 50};
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
  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::drawSolidRect(cinder::Rectf
                                (0, 0, 800, 800));
  cinder::gl::color(0.650, 0.854, 0.564);
  cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                       (265, 75, 790, 590), 20);

  cinder::gl::color(Color::white());
  cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                       (271, 80, 785, 584), 20);

  cinder::gl::color(Color::black());
}

//Displays Cheat box and text box
void myapp::WordSearch::DisplayCheat() {
  cinder::gl::color(1, 0, 0);
  cinder::gl::drawStrokedRect(cinder::Rectf
                                  (60, 500, 90, 530), 5);
  PrintText("HINT", {140, 530});
  cinder::gl::color(Color::black());

}

void myapp::WordSearch::keyDown(cinder::app::KeyEvent event) {
  if (event.isAltDown()) {
    type_x_loc = 125;
    cinder::gl::color(Color::white());
    cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                         (100, 650, 500, 700), 70);
    if (InWordBank(build_word) && AlreadyAnswered(build_word)) {
      cinder::gl::color(Color::black());
      PrintText("ALREADY \n ANSWERED!", {680, 690});

    } else if (InWordBank(build_word) && !AlreadyAnswered(build_word)) {
      word_to_highlight.clear();
      cinder::gl::color(Color::black());
      PrintText("CORRECT!", {680, 690});


      word_to_highlight = build_word;
      already_answered.push_back(build_word);
      patternSearch();

    } else {
      cinder::gl::color(Color::black());
      PrintText("INCORRECT! \nTRY AGAIN!", {680, 690});
    }
    build_word.clear();
    return;

  } else if (event.getChar()) {
    cinder::gl::color(0.988, 0.980, 0.835);
    cinder::gl::drawSolidRect(cinder::Rectf(601, 650, 800, 800));
    cinder::gl::color(Color::black());
    string this_char(1, toupper(event.getChar()));
    build_word.append(this_char);
    cinder::vec2 text_loc = {type_x_loc, 690};
    type_x_loc += 11;
    PrintText(this_char, text_loc);
  }

  //If shift is pressed, mark cheat box red
  if (event.isShiftDown()) {
    DrawSquares();
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawSolidRect(cinder::Rectf
                                  (60, 500, 90, 530));
  }
}

void myapp::WordSearch::keyUp(cinder::app::KeyEvent event) {

  //If shift is not being pressed, keep cheat box unmarked
  if (!event.isShiftDown()) {
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawStrokedRect(cinder::Rectf
                                    (60, 500, 90, 530), 5);
    cinder::gl::color(Color::white());
    cinder::gl::drawSolidRect(cinder::Rectf
                                  (62, 502, 88, 528));

    int left_start = 275;
    int right_start = 296;
    int bottom_start = 106;
    int top_start = 85;
    int increment = 25;

    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        if (valid_letter[i][j]) {
          cinder::gl::color(Color::white());
          cinder::gl::drawStrokedRect(cinder::Rectf(left_start,
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

}

bool myapp::WordSearch::AlreadyAnswered(string build_word) {
  bool found = false;
  for (auto aa = already_answered.begin(); aa != already_answered.end(); ++aa) {
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

void myapp::WordSearch::DrawUIBackground() {

  //Words Found
  cinder::gl::color(0.650, 0.854, 0.564);
  cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                       (35, 75, 235, 590), 20);

  cinder::gl::color(Color::white());
  cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                       (40, 80, 230, 584), 20);

  //Word Counter
  cinder::gl::color(0.964, 0.694, 0.937);
  cinder::gl::drawSolidRect(cinder::Rectf(40, 0, 230, 50));

  cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                       (40, 0, 230, 70), 20);

  cinder::gl::color(Color::black());
  cinder::gl::drawStrokedRoundedRect(cinder::Rectf
                                         (100, 650, 600, 700), 70);
  cinder::gl::color(Color::white());
  cinder::gl::drawSolidRoundedRect(cinder::Rectf
                                       (100, 650, 600, 700), 70);
  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::drawSolidRect(cinder::Rectf(601, 650, 800, 800));

  cinder::gl::color(Color::black());

}

void myapp::WordSearch::DisplayWordCounter() {
  cinder::gl::color(Color::black());
  cinder::vec2 loc_words = {170, 50};
  PrintText(std::to_string(words_left), loc_words);
}

void myapp::WordSearch::DisplayTitle() {
  cinder::gl::color(0.964, 0.694, 0.937);
  PrintText("SEARCH IT!", {400, 60});
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
        cinder::gl::drawStrokedRect(cinder::Rectf(left_start,
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

bool myapp::WordSearch::search2DCol(int col_count) {
  col_string.clear();
  for (int row = 0; row < 20; row++) {
    col_string.append(map[row][col_count]);
    col_loc = col_count;
  }
  row_index_found = col_string.find(word_to_highlight);
  if (row_index_found == -1) {
    return false;
  } else {
    row_loc = row_index_found;
    col_string.clear();
    std::cout << row_loc << " " << col_loc << " ";
    for (int i = row_loc; i < word_to_highlight.length(); i++) {
      answered_correctly[i][col_loc] = true;
    }
    return true;
  }

}

bool myapp::WordSearch::search2DRow(int row_count) {
  row_string.clear();
  for (int col = 0; col < 20; col++) {
    row_string.append(map[row_count][col]);
    row_loc = row_count;
  }
  col_index_found = row_string.find(word_to_highlight);

  std::cout << row_string << " " << col_index_found << "\n";
  if (col_index_found == -1) {
    return false;
  } else {
    col_loc = col_index_found;
    row_string.clear();
    col_string.clear();
    for (int i = col_loc; i < word_to_highlight.length(); i++) {
      answered_correctly[row_loc][i] = true;
    }
    return true;
  }
}

void myapp::WordSearch::patternSearch() {
  col_index_found = -1;
  row_index_found = -1;

  row_loc = 0;
  col_loc = 0;
  if (word_to_highlight.length() % 2 != 0) {
    for (int i = 0; i < 20; i++) {
      if (search2DRow(i)) {
        return;
      }
    }
  }
  if (word_to_highlight.length() % 2 == 0) {
    for (int i = 0; i < 20; i++) {
      if (search2DCol(i)) {
        return;
      }
    }
  }
}

void myapp::WordSearch::HighlightWords() {
  int left_start = 277;
  int right_start = 298;
  int bottom_start = 108;
  int top_start = 84;
  int increment = 25;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      if (answered_correctly[i][j]) {
        cinder::gl::color(0.650, 0.854, 0.564);
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
