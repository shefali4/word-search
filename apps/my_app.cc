// Copyright (c) 2020 Shefali Sharma. All rights reserved.

#include "my_app.h"
#include <cinder/gl/gl.h>
#include <cinder/Text.h>
#include "cinder/Rect.h"
#include <list>
#include <cinder/app/App.h>
#include <SFML/Window.hpp>
#include <cinder/audio/Voice.h>
#include <iostream>
#include <fstream>
#include "hint.h"

namespace myapp {

using namespace std;
using namespace ci;
using cinder::app::KeyEvent;
using cinder::TextBox;
using cinder::Color;
using cinder::ColorA;

int col_index_found = -1;
int row_index_found = -1;
int count = 0;
int type_x_loc = 400;
int itr_count = 0;
const char kNormalFont[] = "Baskerville";

string words[] = {};
ci::audio::VoiceRef mBackground;
ci::audio::VoiceRef mTyping;
ci::audio::VoiceRef mCorrect;
ci::audio::VoiceRef mIncorrect;
ci::audio::VoiceRef mHint;
ci::audio::VoiceRef mEndGame;


WordSearch::WordSearch()
    :state_{GameState::kPlaying} {}

void WordSearch::setup() {
  word_bank.clear();
  timer.start(0);

  //Audio Files
  audio::SourceFileRef background_audio =
      audio::load(app::loadAsset("puzzle.ogg"));
  mBackground = audio::Voice::create(background_audio);
  mBackground->start();

  audio::SourceFileRef correct_audio =
      audio::load(app::loadAsset("correct.mp3"));
  mCorrect = audio::Voice::create(correct_audio);

  audio::SourceFileRef incorrect_audio =
      audio::load(app::loadAsset("incorrect.mp3"));
  mIncorrect = audio::Voice::create(incorrect_audio);

  audio::SourceFileRef typing_audio =
      audio::load(app::loadAsset("type.mp3"));
  mTyping = audio::Voice::create(typing_audio);

  audio::SourceFileRef end_game_audio =
      audio::load(app::loadAsset("cheer.wav"));
  mEndGame = audio::Voice::create(end_game_audio);

  audio::SourceFileRef hint_audio =
      audio::load(app::loadAsset("hint.wav"));
  mHint = audio::Voice::create(hint_audio);
}

void WordSearch::update() {
  KeyEvent event;
  keyDown(event);
  HighlightWords();
}

void WordSearch::draw() {
  DisplayWordsFound();
  if (count == 0) {
    ReadFile();
    InitializeEmpty();
    InsertWords();
    myapp::Display display;
    display.DrawComponents();
    RandomLetters();
    DisplayFilledGrid();
    myapp::Hint hint;
    hint.DisplayHint();
    DrawHeaders();
    count++;
  }
  UpdateCounter();
}

void myapp::WordSearch::PrintText(const std::string &text,
                                  const glm::vec2 &loc) {
  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 20))
      .size({400, 50})
      .color(Color::white())
      .backgroundColor(
          ColorA(1, 0.988, 0.839, 0))
      .text(text);
  const auto text_size = box.getSize();
  const cinder::vec2 text_loc =
      {loc.x - text_size.x / 2, loc.y - text_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, text_loc);
}

void WordSearch::ReadFile() {

  //Reads puzzle file path
  ifstream puzzle_file("/Users/shefalisharma/"
                  "software/Cinder/my-projects/"
                  "final-project-shefali4/assets/puzzle.spf");

  if (puzzle_file.fail()) {
    cout << "The entered filepath is not valid.";
    return;
  }

  string line;
  while (getline(puzzle_file, line)) {
    file_words.push_back(line);
  }

  puzzle_file.close();

  //List to Array
  words_size = file_words.size();
  words = new string[words_size];
  int counter = 0;
  for (auto & itr : file_words) {
    words[counter] = itr;
    counter++;
  }
}

void myapp::WordSearch::InitializeEmpty() {
  int loc_x = 288;
  int loc_y = 110;
  cinder::gl::color(Color::black());

  //Initialize board to '_' and false
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      cinder::vec2 loc = {loc_x, loc_y};
      grid[i][j] = "_";
      valid_letter[i][j] = false;
      answered_correctly[i][j] = false;
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }

  //Fills word bank list
  for (int i = 0; i < words_size; i++) {
    word_bank.push_back(words[i]);
  }
}

void myapp::WordSearch::DisplayWordsFound() {

  //Print word bank words found
  int loc_y_words = 130;
  if (already_answered.size() > itr_count) {
    for (auto & itr : already_answered) {
      loc_y_words += 35;
      cinder::gl::color(1,0,0);
      PrintText(itr, {135, loc_y_words});
    }
    itr_count++;
  }
}

//Insert word bank words into grid
void myapp::WordSearch::InsertWords() {
  int row = 0;
  int col = 0;

  for (int j = 0; j < words_size; j++) {
    string word = words[0];

    //if word length is even, place word vertically
    if (words[j].length() % 2 == 0) {
      row = rand() % 10;
      col = rand() % 20;

      for (int even = 0; even < words[j].length(); even++) {
        if (grid[row][col] == "_") {
          if (CheckNextEven(words[j].length(), row, col)) {
            PerWord(even, row, col, j);
            row++;
          }
        } else {
          word_bank.remove(words[j]);
          break;
        }
      }
    }

    //if word length is odd, place word horizontally
    if (words[j].length() % 2 != 0) {
      row = rand() % 20;
      col = rand() % 4;
      for (int odd = 0; odd < words[j].length(); odd++) {
        if (grid[row][col] == "_") {
          if (CheckNextOdd(words[j].length(), row, col)) {
            PerWord(odd, row, col, j);
            col++;
          }
        } else {
          word_bank.remove(words[j]);
          break;
        }
      }
    }
  }

  words_left = word_bank.size();
}

//Checks if rest of word is inserted
bool myapp::WordSearch::CheckNextEven(int word_length, int row, int col) {
  for (int i = row; i < word_length; i++) {
    if (!(grid[row][col] == "_")) {
      return false;
    }
  }
  return true;
}

//Checks if rest of word is inserted
bool myapp::WordSearch::CheckNextOdd(int word_length, int row, int col) {
  for (int i = col; i < word_length; i++) {
    if (!(grid[row][col] == "_")) {
      return false;
    }
  }
  return true;
}

//Places letters horizontally/vertically depending on row/col values
void myapp::WordSearch::PerWord(int index, int row, int col, int j) {
  string word = words[j];
  char each_char = toupper(word.at(index));
  string string_char(1, each_char);
  grid[row][col] = string_char;
  valid_letter[row][col] = true;
}

//Chooses random letters excluding vowels
void myapp::WordSearch::RandomLetters() {
  char letters[] = "bcdfghjklmnpqrstvwxz";
  srand(time(nullptr));
  char random_char;
  for (auto & row : grid) {
    for (auto & col : row) {
      if (col == "_") {
        random_char = toupper(letters[rand() % 20]);
        col = random_char;
      }
    }
  }
}

//Fills cells with letters in the grid
void myapp::WordSearch::DisplayFilledGrid() {
  int loc_x = 288;
  int loc_y = 110;

  for (auto & row : grid) {
    for (const auto & col : row) {
      cinder::vec2 loc = {loc_x, loc_y};
      PrintText(col, loc);
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }
}

void myapp::WordSearch::keyDown(cinder::app::KeyEvent event) {

  //If Alt is pressed, check if answer is correct, incorrect, or already
  // answered
  if (event.isAltDown()) {
    type_x_loc = 400;
    cinder::gl::color(Color::white());
    cinder::gl::drawSolidRoundedRect(
        cinder::Rectf(271, 650, 785, 700),
        70);
    AltOptions();
    return;

  } else if (event.getChar()) {
    mTyping->start();
    cinder::gl::color(0.988, 0.980, 0.835);
    cinder::gl::drawSolidRect(
        cinder::Rectf(30, 650, 250, 800));
    cinder::gl::color(Color::black());
    string each_char(1, toupper(event.getChar()));
    typed_word.append(each_char);
    cinder::vec2 text_loc = {type_x_loc, 690};
    type_x_loc += 17;
    PrintText(each_char, text_loc);
  }

  //If shift is pressed, mark hint box red
  if (event.isShiftDown()) {
    DrawSquares();
    mHint->start();
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawSolidRect(cinder::Rectf
                                  (75, 500, 105, 530));
  }

  if (event.isControlDown()) {
    HelpButton();
  }
}

void myapp::WordSearch::AltOptions() {

  //Already Answered
  if (InWordBank(typed_word) && AlreadyAnswered(typed_word)) {
    cinder::gl::color(Color::black());
    PrintText("ALREADY \n ANSWERED!", {145, 680});
    PrintText("SEARCH: ", {330, 689});

    //Correct Answer
  } else if (InWordBank(typed_word) && !AlreadyAnswered(typed_word)) {
    word_to_highlight.clear();
    mCorrect->start();
    cinder::gl::color(Color::black());
    PrintText("CORRECT!", {146, 690});
    cinder::gl::color(0,1,0);
    PrintText("CORRECT!", {145, 689});
    cinder::gl::color(Color::black());
    PrintText("SEARCH: ", {330, 689});
    words_left--;
    word_to_highlight = typed_word;
    already_answered.push_back(typed_word);
    SearchPattern();

    //Incorrect Answer
  } else {
    mIncorrect->start();
    cinder::gl::color(Color::black());
    PrintText("INCORRECT! \nTRY AGAIN!", {146, 681});
    cinder::gl::color(1,0,0);
    PrintText("INCORRECT! \nTRY AGAIN!", {145, 680});
    cinder::gl::color(Color::black());
    PrintText("SEARCH: ", {330, 689});
  }
  typed_word.clear();
}

void myapp::WordSearch::keyUp(cinder::app::KeyEvent event) {
  mTyping->stop();

  //If Help button is not pressed
  if (!event.isControlDown()) {
    cinder::gl::color(0.988, 0.980, 0.835);
    cinder::gl::drawSolidRect(
        cinder::Rectf(240, 705, 790, 790));
  }

  //If shift is not being pressed, keep hint box unmarked
  if (!event.isShiftDown()) {
    mHint->stop();
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawStrokedRect(
        cinder::Rectf(75, 500, 105, 530),
        3);
    cinder::gl::color(Color::white());
    cinder::gl::drawSolidRect(cinder::Rectf
                                  (77, 502, 103, 528));
    int left_start = 277;
    int right_start = 298;
    int bottom_start = 108;
    int top_start = 85;
    int increment = 25;

    for (auto & i : valid_letter) {
      for (bool j : i) {
        if (j) {
          cinder::gl::color(Color::white());
          cinder::gl::drawStrokedRect(
              cinder::Rectf(left_start,top_start,
                  right_start,bottom_start),7);
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

//Check if word has already been answered
bool myapp::WordSearch::AlreadyAnswered(string typed_word) {
  for (auto & answer : already_answered) {
    if (answer == typed_word) {
      return true;
    }
  }
  return false;
}

//Check if word is in word bank
bool myapp::WordSearch::InWordBank(string typed_word) {
  for (auto & itr : word_bank) {
    if (itr == typed_word) {
      return true;
    }
  }
  return false;
}

//Squares drawn around correct letters for hint button
void myapp::WordSearch::DrawSquares() {
  int left_start = 277;
  int right_start = 298;
  int bottom_start = 108;
  int top_start = 85;
  int increment = 25;

  for (auto & i : valid_letter) {
    for (bool j : i) {
      if (j) {
        cinder::gl::color(0, 1, 0);
        cinder::gl::drawStrokedRect(
            cinder::Rectf(left_start,top_start,right_start,bottom_start));
      }
      left_start += increment;
      right_start += increment;
    }
    left_start = 277;
    right_start = 298;
    top_start += increment;
    bottom_start += increment;
  }
}

//Seach for location of answer in grid -- column
bool myapp::WordSearch::Search2DCol(int col_count) {
  col_string.clear();
  for (auto & row : grid) {
    col_string.append(row[col_count]);
    col_loc = col_count;
  }
  row_index_found = col_string.find(word_to_highlight);
  if (row_index_found == -1) {
    return false;
  } else {
    row_loc = row_index_found;
    col_string.clear();
    for (int i = row_loc; i < word_to_highlight.length(); i++) {
      answered_correctly[i][col_loc] = true;
    }
    return true;
  }
}

//Seach for location of answer in grid -- row
bool myapp::WordSearch::Search2DRow(int row_count) {
  row_string.clear();
  for (int col = 0; col < 20; col++) {
    row_string.append(grid[row_count][col]);
    row_loc = row_count;
  }
  col_index_found = row_string.find(word_to_highlight);
  if (col_index_found == -1) {
    return false;
  } else {
    col_loc = col_index_found;
    row_string.clear();
    col_string.clear();
    for (int i = col_loc; i < word_to_highlight.length() + 1; i++) {
      answered_correctly[row_loc][i] = true;
    }
    return true;
  }
}

//Searches row and column for location of word
void myapp::WordSearch::SearchPattern() {

  //Checks if length is odd, then checks rows
  if (word_to_highlight.length() % 2 != 0) {
    for (int i = 0; i < 20; i++) {
      if (Search2DRow(i)) {
        return;
      }
    }
  }

  //Checks if length is even, then checks columns
  if (word_to_highlight.length() % 2 == 0) {
    for (int i = 0; i < 20; i++) {
      if (Search2DCol(i)) {
        return;
      }
    }
  }
}

//Updates word counter
void myapp::WordSearch::UpdateCounter() {
  gl::color(Color::white());
  gl::drawSolidRect(Rectf(160, 0, 190, 50));
  gl::color(Color::black());
  cinder::vec2 loc_words = {174, 44};

  PrintText(to_string(words_left), loc_words);
  if (words_left == 0) {
    YouWin();
  }
}

//Controls You Win Screen
void myapp::WordSearch::YouWin() {
  timer.stop();
  mEndGame->start();

  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::drawSolidRect(
      cinder::Rectf(0, 0, 800, 800));
  cinder::gl::color(Color::black());
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(150, 150, 650, 650),
      40);

  cinder::gl::color(Color::white());
  PrintText("YOU WIN! NICE JOB!", {400, 520});
  PrintText("YOU FINISHED THE PUZZLE IN ",{400,250});
  PrintText(std::to_string(timer.getSeconds()),
            {400,330});
  PrintText("SECONDS!",{400,410});
}

//Cover word in green once answered correctly
void myapp::WordSearch::HighlightWords() {
  double left_start = 277;
  double right_start = 302;
  double bottom_start = 110;
  double top_start = 84;
  double increment = 25;

  for (auto & i : answered_correctly) {
    for (bool j : i) {
      if (j) {
        cinder::gl::color(0.650, 0.854, 0.564);
        cinder::gl::drawSolidRect(
            cinder::Rectf(left_start,top_start,right_start,bottom_start));
      }
      left_start += increment;
      right_start += increment;
    }
    left_start = 277;
    right_start = 302;
    top_start += increment;
    bottom_start += increment;
  }
}

//Writes headers for major UI components
void myapp::WordSearch::DrawHeaders() {
  cinder::gl::color(Color::white());
  PrintText("SEARCH IT!", {401, 61});
  cinder::gl::color(Color::black());
  PrintText("SEARCH IT!", {400, 60});
  PrintText("SEARCH: ", {330, 689});
  PrintText("HINT", {150, 530});
  PrintText("Words Found:", {140, 130});
  PrintText("Words Left: ", {115, 45});
  PrintText("?", {755, 40});
}

void myapp::WordSearch::HelpButton() {
  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::color(Color::black());
  cinder::gl::color(0.631, 0.929, 0.949);
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(271, 710, 785, 780), 20);
  cinder::gl::color(Color::white());
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(274, 713, 782, 777), 18);
  cinder::gl::color(Color::black());
  PrintText("Help:", {340, 750});
  PrintText("Click Alt to Enter Word", {600, 740});
  PrintText("Click Shift to Use Hint", {600, 770});
}
}// namespace myapp
