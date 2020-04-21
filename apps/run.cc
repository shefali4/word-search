// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#include "my_app.h"


using cinder::app::App;
using cinder::app::RendererGl;

namespace myapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  //settings->setWindowSize(kWidth, kHeight);
  //settings->setTitle("My CS 126 Application");

  sf::RenderWindow window(sf::VideoMode(800, 800), "CS 126 Final Project");

// The main loop - ends as soon as the window is closed
  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      // Request for closing the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Activate the window for OpenGL rendering

    window.display();
  }

}


}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::WordSearch, RendererGl(RendererGl::Options().msaa(myapp::kSamples)), myapp::SetUp)
