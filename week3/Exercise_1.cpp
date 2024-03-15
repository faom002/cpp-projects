#include <raylib.h>
int main() {

  // initialize the window
  InitWindow(400, 300, "Example");

  // keeps the window running
  while (not WindowShouldClose()) {

    //begins drawing  
    BeginDrawing();

    // gives a background color darkblue
    ClearBackground(DARKBLUE);

    // shows the fps at the top
    DrawFPS(0, 0);

    //ends the drawing
    EndDrawing();

  }

  // close the window
  CloseWindow();
  return 0;
}
