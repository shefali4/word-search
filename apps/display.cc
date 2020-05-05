//
// Created by Shefali Sharma on 5/4/20.
//

#include "hint.h"
#include "cinder/Rect.h"
#include <cinder/Text.h>
#include <cinder/gl/gl.h>
#include "display.h"

using cinder::Color;
using cinder::ColorA;

namespace myapp {


void myapp::Display::DrawComponents() {

  //Draw Grid
  cinder::gl::lineWidth(100);
  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::drawSolidRect(cinder::Rectf
                                (0, 0, 800, 800));
  cinder::gl::color(0.650, 0.854, 0.564);
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(265, 75, 790, 590), 20);
  cinder::gl::color(Color::white());
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(271, 80, 785, 584),
      10);


  //Words Found
  cinder::gl::color(0.650, 0.854, 0.564);
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(35, 75, 235, 590), 18);

  cinder::gl::color(cinder::Color::white());
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(40, 80, 230, 584), 20);


  //Word Counter
  cinder::gl::color(0.964, 0.694, 0.937);

  cinder::gl::drawSolidRect(
      cinder::Rectf(40, 0, 230, 20));

  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(40, 0, 230, 60), 20);

  cinder::gl::color(cinder::Color::white());
  cinder::gl::drawSolidRect(
      cinder::Rectf(44, 0, 226, 20));

  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(44, 0, 226, 56), 18);


  //Search Bar
  cinder::gl::color(cinder::Color::black());
  cinder::gl::drawStrokedRoundedRect(
      cinder::Rectf(
          271, 650, 785, 700), 70);
  cinder::gl::color(cinder::Color::white());
  cinder::gl::drawSolidRoundedRect(
      cinder::Rectf(
          271, 650, 785, 700), 70);


  //Cover Search Bar Extra Outline
  cinder::gl::color(0.988, 0.980, 0.835);
  cinder::gl::drawSolidRect(cinder::Rectf(
      786, 650, 800, 800));


  cinder::gl::color(cinder::Color::black());
}
}// namespace myapp
