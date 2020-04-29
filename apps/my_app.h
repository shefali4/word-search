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

namespace myapp {

enum class GameState {
  kPlaying,
  kGameOver,
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
  static void PrintText(const std::string& text,
                 const glm::vec2& loc);

  /**
   * Creates empty grid with '_' in each spot
   */
  void InitializeEmpty();

  /**
   * Draws grid 20 x 20
   */
  static void DrawGrid();

  /**
   * Collects all the correct words the player has found
   */
  static void DisplayWordsFound();

  /**
   * Inserts the words from the word bank into the grid
   */
  void InsertWords();

  /**
   * Inserts random letters
   */
  void RandomLetters();

  /**
   * Displays table
   */
  void DisplayFilledGrid();

  /**
   * Checks if Cheat button has been accessed
   * @param event key event
   */
  void keyDown(cinder::app::KeyEvent event) override;

  /**
   * Controls Cheat button
   * @param event key event
   */
  void keyUp(cinder::app::KeyEvent event) override ;

  /**
   * Displays hint box and hint text
   */
  void DisplayCheat();

  /**
   *
   * @param c
   * @param row
   * @param col
   * @param j
   */
  void PerWord(int c, int row, int col, int j);

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
   * Reduces count for each word answered correctly
   */
  void DisplayWordCounter();

  /**
   * Displays Word Search title at top of screen
   */
  void DisplayTitle();

  /**
   * Draws Squares to highlight grid and word bank section
   */
  void DrawUIBackground();

  /**
   * Searches for word to mark correct on grid
   */
  void patternSearch();

  /**
   * Searches for word vertically
   * @param col_count
   * @return
   */
  bool search2DCol(int col_count);

  /**
   * Searches for word horizontally
   * @param row_count
   * @return
   */
  bool search2DRow(int row_count);

  /**
   * Controls what happens when game is over
   */
  void GameOver();

  /**
   * Highlights word on grid if found
   */
  void HighlightWords();
 private:
  sf::String map[20][20];
  GameState state_;
  bool valid_letter[20][20];
  bool answered_correctly[20][20];
  cinder::Timer timer;


};
}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
