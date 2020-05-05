//
// Created by Shefali Sharma on 5/1/20.
//

#include "cinder/Rect.h"
#include <cinder/Text.h>
#include <cinder/gl/gl.h>
#include "my_app.h"
#include "hint.h"


namespace myapp {

void Hint::DisplayHint() {
  cinder::gl::color(1, 0, 0);
  cinder::gl::drawStrokedRect(
      cinder::Rectf(75, 500, 105, 530), 5);
  cinder::gl::color(cinder::Color::black());
}
}// namespace myapp
