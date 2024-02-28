#include "window.h"
#include <iostream>
#include <memory>
#include <optional>
class Circle {

private:
  Window window;
  int circle_radius = 80;
  std::optional<int> circle_pos_x = window.get_height() / 2;
  std::optional<int> circle_pos_y = window.get_width() / 2;

  std::optional<int> keep_the_original_value_x = circle_pos_x.value_or(0);
  std::optional<int> keep_the_original_value_y = circle_pos_y.value_or(0);

  int move_circle_away(int circle_pos_x) { return circle_pos_x + 2; }

public:
  // change the color of circle
  void change_color_circle() {

    Vector2 mouse_pos_xy = GetMousePosition();
    std::cout << "circle y pos " << circle_pos_y.value() << "\n";
    // std::cout << "circle x pos " << circle_pos_x.value() << "\n";
    // std::cout << "mouse pos x " << mouse_pos_xy.x << "\n";
    std::cout << "mouse pos y " << mouse_pos_xy.y << "\n";

    if (mouse_pos_xy.x == circle_pos_x.value() ||
        mouse_pos_xy.y == circle_pos_y.value()) {

        
        circle_pos_x = move_circle_away(circle_pos_x.value());


      DrawCircle(this->circle_pos_y.value(), this->circle_pos_x.value(),
                 this->circle_radius, Color(RED));

    } else {
        circle_pos_x = keep_the_original_value_x.value();
      DrawCircle(this->circle_pos_y.value(), this->circle_pos_x.value(),
                 this->circle_radius, Color(BLACK));
    }
  }
};
