#include <iostream>
#include <memory>
#include <raylib.h>

#include "headers/Entity.h"
#include "headers/RectangleComponent.h"

int main() {

  auto number_component = Entity::create();
  number_component->Attach(std::make_shared<RectangleComponent>());



  // initialize window
  InitWindow(1200, 800, "rectangles");


 SetTargetFPS(60);
  while (not WindowShouldClose()) {
  
  

BeginDrawing();



  for (auto &elem : number_component->components) {

      elem->draw_rectangle_component();

  }


EndDrawing();

  }

CloseWindow();

  return 0;
}
