
#ifndef NUMBERCOMPONENT_H
#define NUMBERCOMPONENT_H

#include "Components.h"
#include <cmath>
#include <raylib.h>

struct RectangleComponent : public Component {
  void draw_rectangle_component() override {
    float speed = 50.0f; // set my choice for how fast it should go
    float deltaTime = 20.0f;

    float accumulator;



    while (accumulator >= speed) {

    accumulator += deltaTime;
      // Calculate color components using sine waves to create a smooth color
      // transition
      unsigned char r = static_cast<unsigned char>(accumulator);
      unsigned char g = static_cast<unsigned char>(accumulator);
      unsigned char b = static_cast<unsigned char>(accumulator);
      unsigned char a = static_cast<unsigned char>(accumulator);

      ClearBackground(WHITE); // Clear the background

      DrawRectangle(1200 / 2, 800 / 2, 500, 500,
                    Color{r, g, b, a}); // Draw the rectangle

      accumulator -= speed;
    }
  };
};

#endif
