#pragma once
#include <raylib.h>
class Window {
private:
  int screen_height;
  int screen_width;
  const char *title;

public:
friend class Cricle;
  Window(int screen_height = 1200, int screen_width = 800,
         const char *title = "cirle Game")
      : screen_height(screen_height), screen_width(screen_width), title(title) {


  }

void initialize_window(){


    InitWindow(this->screen_width, this->screen_height, this->title);

}

  int get_height() { return this->screen_height; }

  int get_width() { return this->screen_width; }
};
