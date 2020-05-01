//
// Created by Shefali Sharma on 5/1/20.
//

#ifndef FINALPROJECT_APPS_MY_APP_CC_GRID_H_
#define FINALPROJECT_APPS_MY_APP_CC_GRID_H_

namespace myapp {

class Grid {
 public:
  void DisplayWordsFound();
  void InsertWords();
  void PerWord(int index, int row, int col, int j);
  void DisplayFilledGrid();
  void DrawGrid();
};
}
#endif //FINALPROJECT_APPS_MY_APP_CC_GRID_H_
