// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <SFML/Window.hpp>
#include "my_app.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings *settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
  settings->setResizable(false);
}
}

// This is a macro that runs the application.
CINDER_APP(myapp::WordSearch, RendererGl(RendererGl::Options().msaa(myapp::kSamples)), myapp::SetUp)
