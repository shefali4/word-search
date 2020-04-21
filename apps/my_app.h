// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <mylibrary/example.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


namespace myapp {

class WordSearch : public cinder::app::App {
 public:
  WordSearch();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void PrintText(const std::string& text,
                             const glm::vec2& loc);
  void InitializeEmpty();
  void DrawGrid();
  void DrawSquares();
  void WordBank();
  void InsertWords();
  void RandomLetters();
  void Display();

  void make_board();
  void update_mouse_pressed(sf::Vector2f mpos);
  void user_interaction(sf::Color col);
  void Cheat();
  void PerWord(int c, int row, int col, int j);
 private:
  std::string map[20][20];


  float fX, fY;                                // Dimensions of desktop
  std::string fDifficulty;                     // Difficulty of WS
  int fNShort, fNMedium, fNLong;

  // Handle the board
  int fRow, fCol;                              // Dimensions
  int fMinRow, fMinCol;                        // Min row/cols
  int fMaxRow, fMaxCol;                        // Max row/cols
  double fDx;                                  // Lattice size for text size, I chose .7*fDx
  sf::Color fBoardColor;                       // VertexArray color
  sf::VertexArray fLine;                       // Need a VA for the fBoard vector
  std::vector<sf::VertexArray> fBoard;         // Make a grid

  // Handle Colors
  std::map<int,sf::RectangleShape> fSquares;   // This is necessary to change colors
  std::map<int,int> fIDrow, fIDcol;            // ID->Row, ID->Col
  std::map<int,std::map<int,int> > fRowColID;  // Row/Col -> ID



  // Common Iterators, no explanations:
  std::map<int,int>::iterator fMii;
  std::string::iterator fStr;
  std::set<int>::iterator fSi;
  std::vector<std::string>::iterator fVstr;
  std::map<int,sf::RectangleShape>::iterator fMir;
  std::map<int,std::set<int> >::iterator fMisi;
  std::map<int,sf::Text>::iterator fMitxt;

  // The Letters and Handling the Board letters:
  std::map<std::string,int> fDirMap;    // Directional map, keeps it easy to read
  std::map<int,std::string> fDirMapInv; // The inverse of the above
  sf::Font fFont;                       // SFML font loader
  sf::Text fText;                       // SFML text loader
  std::map<int,sf::Text> fLetters;      // Letters physically on the board
  std::set<int> fListOfIDs;             // Easy access set with all IDs to be drawn
  std::map<int,char> fAlphabet;         // Alphabet for random letters
  std::vector<std::string> fWords;      // Vector of Words
  std::map<int,std::set<int> > fWordIDs;// List of all words in the form if IDs, key=dummy, val is ID
  int fWordCount;

  // The dictionary and word generation

  std::map<int,std::vector<std::string> > fRandomWords; // Organize dict words by string length
  std::map<std::string,int> fWordLength;                // Map for human readibility
  std::map<int,int> fNWordsGen;  // Based on difficulty, generate varying #s of short/med/long words

  // Make the LHS information
  float fOffsetX;                              // I'd like to put stuff on the LHS
  float fMaxLHSX;                              // In order to center LHS size / objects
  std::vector<sf::Text> fLHSInformation;       // All the words to be displayed

  std::map<int,int> fWordScratchMap;
  std::vector<sf::VertexArray> fScratchedOut;

  // User functionality:
  sf::Color fUserColor, fFoundColor;
  bool fUserAttempt;
  bool fCheatStatus;
  int fInitialClick, fFinalClick;
  std::set<int> fUserFilledBlocks, fUserAttemptToFindWord;

  // Completion of the game
  bool fSuccess;
  sf::Time fCutOffTime;
  std::vector<sf::Text> fComplete, fCompleteDummy;
  int fSuccessCount;




};


}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
