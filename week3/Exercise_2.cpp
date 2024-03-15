#include "headers/circle.h"
#include "headers/window.h"
#include <chrono>
#include <raylib.h>

using namespace std::chrono;
int main() {

  Window window;
  Circle circle;

  window.initialize_window();

  // fps = # frames / (current time - start time)
  int frames = 0;
  auto start_time = system_clock::now();

  while (not WindowShouldClose()) {

    auto end_time = system_clock::now();
    frames++;

    auto elapsed_seconds =
        duration_cast<seconds>(end_time - start_time).count();

    auto fps = (elapsed_seconds != 0) ? (frames / elapsed_seconds) : 0;

    BeginDrawing();

    DrawText(TextFormat("chrono calculation %i ", fps), 0, 0, 20, Color(BLACK));
    // DrawFPS(1, 1); method

    ClearBackground(DARKBLUE);
    circle.change_color_circle();

    EndDrawing();
  }

  return 0;
}
