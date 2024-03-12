#pragma once
#include "Components.h"
#include <cmath>
#include <raylib.h>

struct RectangleComponent : public Component {
  void Draw() override {

    ClearBackground(WHITE);

    DrawRectangle(1200 / 2, 800 / 2, 500, 500, Color(RED));
  };
};

