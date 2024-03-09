
#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "Components.h"
#include <cmath>
#include <raylib.h>

struct RectangleComponent : public Component {
  void draw_rectangle_component() override {

    ClearBackground(WHITE);

    DrawRectangle(1200 / 2, 800 / 2, 500, 500, Color(RED));
  };
};

#endif
