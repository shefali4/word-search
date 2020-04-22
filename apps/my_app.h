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

class WordSearch : public cinder::app::App {
 public:
  WordSearch();
  void setup() override;
  void update() override;
  void draw() override;
  //void keyDown(cinder::app::KeyEvent) override;
  void PrintText(const std::string& text,
                             const glm::vec2& loc);
  void InitializeEmpty();
  void DrawGrid();
  void DrawSquares();
  void WordsFound();
  void InsertWords();
  void RandomLetters();
  void Display();
  void keyDown(cinder::app::KeyEvent event) override;
  void keyUp(cinder::app::KeyEvent event) override ;
  void Cheat();
  void PerWord(int c, int row, int col, int j);

  sf::RenderWindow window;
 private:
  sf::String map[20][20];

};


}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
