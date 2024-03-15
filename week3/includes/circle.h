#include "window.h"
#include <iostream>
#include <memory>
#include <optional>
#include <raylib.h>
class Circle {

private:
  Window window;
  int circle_radius = 300;
  std::optional<int> circle_pos_x = window.get_height() / 2;
  std::optional<int> circle_pos_y = window.get_width() / 2;

  std::optional<int> keep_the_original_value_x = circle_pos_x.value_or(0);
  std::optional<int> keep_the_original_value_y = circle_pos_y.value_or(0);

  int move_circle_away(int circle_pos_x) { return circle_pos_x + 2; }

public:
  // change the color of circle
  void change_color_circle() {
DrawText("Moving circle on radius", window.get_height() / 4, window.get_width()/4, 20, Color(BLACK));
      Vector2 circle_pos_xy = {(float)circle_pos_x.value(),(float) circle_pos_y.value()};
    Vector2 mouse_pos_xy = GetMousePosition();
   float distance = Vector2Distance(circle_pos_xy, mouse_pos_xy);
    std::cout << "circle radius pos " << circle_radius << "\n";
    std::cout << "mouse pos y " << distance << "\n";

    if (distance <= circle_radius) {

        
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
