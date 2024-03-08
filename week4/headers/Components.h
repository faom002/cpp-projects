#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

struct Entity;
struct Component {

  std::weak_ptr<Entity> owner;
  virtual void draw_rectangle_component() = 0; // override function
};

#endif


