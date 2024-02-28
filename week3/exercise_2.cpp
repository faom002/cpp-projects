#include "headers/circle.h"
#include "headers/window.h"
#include <raylib.h>

int main() {

  Window window;
  Circle circle;

  window.initialize_window();
  while (not WindowShouldClose()) {

    BeginDrawing();

    ClearBackground(DARKBLUE);
    circle.change_color_circle();

    EndDrawing();
  }

  return 0;
}
