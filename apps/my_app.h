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
  void PrintText(const std::string& text,
                 const glm::vec2& loc);

  /**
   * Creates empty grid with '_' in each spot
   */
  void InitializeEmpty();

  /**
   * Draws grid 20 x 20
   */
  void DrawGrid();

  /**
   * Collects all the correct words the player has found
   */
  void DisplayWordsFound();

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
  void DisplayCheat();
  void PerWord(int c, int row, int col, int j);
  void DrawSquares();
  bool AlreadyAnswered(std::string build_word);
  bool InWordBank(std::string build_word);
  void DisplayWordCounter();
  void DisplayTitle();
  void DrawUIBackground();
  void patternSearch();
  bool search2DCol(int col_count);
  bool search2DRow(int row_count);
  void GameOver();
  void HighlightWords();
 private:
  sf::String map[20][20];
  sf::Window window;
  GameState state_;
  bool valid_letter[20][20];
  bool answered_correctly[20][20];
  cinder::Timer timer;

};
}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
