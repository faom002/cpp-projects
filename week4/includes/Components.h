#pragma once
#include <memory>

struct Entity;
struct Component {

  std::weak_ptr<Entity> owner;
  virtual void Draw() {}; // override function
};




