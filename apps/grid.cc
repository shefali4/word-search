//
// Created by Shefali Sharma on 5/1/20.
//
/*
#include "grid.h"
#include "my_app.h"
//Displays words found in word bank
void myapp::Grid::DisplayWordsFound() {
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
//Inserts words in grid horizontally and vertically based on length of word
void myapp::Grid::InsertWords() {
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
void myapp::Grid::PerWord(int index, int row, int col, int j) {
  string word = words[j];
  char each_char = toupper(word.at(index));
  string string_char(1, each_char);
  map[row][col] = string_char;
}
//Chooses random letters excluding vowels
void myapp::Grid::RandomLetters() {
  char letters[] = "bcdfghjklmnpqrstvwxz";
  srand(time(nullptr));
  char random_char;
  for (auto & row : map) {
    for (int col = 0; col < 20; col++) {
      if (row[col] == "_") {
        random_char = toupper(letters[rand() % 20]);
        row[col] = random_char;
      }
    }
  }
}
void myapp::Grid::DisplayFilledGrid() {
  int loc_x = 288;
  int loc_y = 110;
  gl::color(Color::black());
  cinder::vec2 loc_words_found = {140, 130};
  PrintText("Words Found:", loc_words_found);
  cinder::vec2 loc_words_left = {115, 45};
  PrintText("Words Left: ", loc_words_left);
  for (auto & row : map) {
    for (const auto & col : row) {
      cinder::vec2 loc = {loc_x, loc_y};
      PrintText(col, loc);
      loc_x += 25;
    }
    loc_x = 288;
    loc_y += 25;
  }
}
//Draws grid patterns using rectangle outlines
void myapp::Grid::DrawGrid() {
  gl::lineWidth(100);
  gl::color(0.988, 0.980, 0.835);
  gl::drawSolidRect(Rectf
                                (0, 0, 800, 800));
  gl::color(0.650, 0.854, 0.564);
  gl::drawSolidRoundedRect(
      Rectf(265, 75, 790, 590), 20);
  gl::color(Color::white());
  gl::drawSolidRoundedRect(
      Rectf(271, 80, 785, 584), 20);

  gl::color(Color::black());
}*/