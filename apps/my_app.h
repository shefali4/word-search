// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <mylibrary/example.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cinder/app/KeyEvent.h>
#include <SFML/Audio.hpp>
#include "hint.h"
#include "display.h"
#include <list>

namespace myapp {

enum class GameState {
  kPlaying
};

class WordSearch : public cinder::app::App {
 public:
  WordSearch();
  void setup() override;

  /**
   * Checks if any keys are pressed
   */
  void update() override;

  /**
   * Calls all helper functions in order
   */
  void draw() override;

  /**
   * Prints grid and all text to window
   * @param text string of words needed to be printed
   * @param loc location
   */
  void PrintText(const std::string& text, const glm::vec2& loc);

  /**
   * Creates empty grid with '_' in each spot
   */
  void InitializeEmpty();

  /**
   * Collects all the correct words the player has found
   */
  void DisplayWordsFound();

  /**
   * Inserts the words from the word bank into the grid
   */
  void InsertWords();

  /**
   * Inserts random letters excluding vowels
   */
  void RandomLetters();

  /**
   * Displays grid with filled cells
   */
  void DisplayFilledGrid();

  /**
   * Checks if Hint button has been accessed
   * @param event key event
   */
  void keyDown(cinder::app::KeyEvent event) override;

  /**
   * Controls Hint button
   * @param event key event
   */
  void keyUp(cinder::app::KeyEvent event) override ;

  /**
   * Places letters horizontally/vertically depending on row/col values
   * @param index position of character
   * @param row location of char in row
   * @param col location of char in column
   * @param j which word in list
   */
  void PerWord(int index, int row, int col, int j);

  /**
   * Draws invidible squares over each cell in grid
   */
  void DrawSquares();

  /**
   * Checks if word has already been answered
   * @return boolean
   */
  bool AlreadyAnswered();

  /**
   * Checks if word is in word bank
   * @return boolean
   */
  bool InWordBank();

  /**
   * Writes major headers of UI components
   */
  void DrawHeaders();

  /**
   * Finds row/col location on grid
   */
  void SearchPattern();

  /**
   * Searches for word vertically
   * @param col_count
   * @return boolean
   */
  bool Search2DCol(int col_count);

  /**
   * Searches for word horizontally
   * @param row_count
   * @return boolean
   */
  bool Search2DRow(int row_count);

  /**
   * Displays You Win screen and time took to complete puzzle
   */
  void YouWin();

  /**
   * Highlights word on grid if found
   */
  void HighlightWords();

  /**
   * Reduces count for each word answered correctly
   */
  void UpdateCounter();

  /**
   * Reads words from given file path
   */
  void ReadFile();

  /**
   * Controls different options for when word is entered
   */
  void AltOptions();

  /**
   * Checks if full word has been entered
   * @param word_length length of word
   * @param row location
   * @param col location
   * @return boolean
   */
  bool CheckNextEven(int word_length, int row, int col);

  /**
   * Checks if full word has been entered
   * @param word_length length of word
   * @param row location
   * @param col location
   * @return boolean
   */
  bool CheckNextOdd(int word_length, int row, int col);

 private:
  bool valid_letter[20][20];
  bool answered_correctly[20][20];
  int row_loc;
  int col_loc;
  int words_size;
  int words_left;
  sf::String grid[20][20];
  std::list<std::string> word_bank;
  std::string typed_word;
  std::string col_string;
  std::string word_to_highlight;
  std::string row_string;
  std::string *words;
  cinder::Timer timer;
  GameState state_;
  std::list<std::string> file_words;
  std::list<std::string> already_answered;
};
} // namespace myapp
#endif  // FINALPROJECT_APPS_MYAPP_H_
