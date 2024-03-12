#pragma once
#include <memory>
#include <vector>
#include "Components.h" 
struct Entity {

  std::vector<std::shared_ptr<Component>>
      components; // were we pass in components

  std::weak_ptr<Entity> self; // owner ship of itself

  // create a object of entity and make weak pointer reference (ptr shared)
  static std::shared_ptr<Entity> create(){

      auto ptr = std::shared_ptr<Entity>(new Entity());
        ptr->self = ptr;

        return ptr;


  };


  void Attach(std::shared_ptr<Component> &&component){

      component->owner = self;
      components.emplace_back(component);


  } // rvalue references
};



