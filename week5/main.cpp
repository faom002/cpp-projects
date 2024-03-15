
#include <complex>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <stdexcept>
#include <vector>

namespace pmall {

struct Entity;

struct Component {

  std::weak_ptr<Entity> owner;

  virtual void Draw(){}

  virtual void Update(float seconds){}
};

struct Transform {
  std::complex<float> position = {0, 0}; // position
  float angle = 0;
  std::complex<float> scale = {1, 1}; // size
};

struct Entity {

  Transform transform;
  std::vector<std::shared_ptr<Component>> components;

  static std::shared_ptr<Entity> make() {

    auto ptr = std::shared_ptr<Entity>(new Entity());

    ptr->self = ptr;

    return ptr;
  }

  void Draw() {

    for (auto &enities : components) {

      enities->Draw();
    }
  }



 void Update(float deltaTimeSeconds) {

    for (auto &enities : components) {

      enities->Update(deltaTimeSeconds);
    }
  }



  void Attach(std::shared_ptr<Component> component) {

    if (component->owner.lock())
      throw std::runtime_error("already attached");
    component->owner = self;
    components.emplace_back(component);
  }

private:
  std::weak_ptr<Entity> self;
  Entity(){};
};

struct Layer {

  std::vector<std::shared_ptr<Entity>> entites;

  void Draw() {

    for (auto &layer : entites) {
      layer->Draw();
    }
  }


  void Update(float deltaTimeSeconds){

      for (auto &layer : entites) {
      layer->Update(deltaTimeSeconds);
      }

  }
};

struct Scene {

  std::vector<Layer> layers;
};

struct RectangleGizmoComponent : public Component {
  std::complex<float> size;

  RectangleGizmoComponent(float width, float height) : size(width, height) {}

  void Draw() override {

    auto parent = owner.lock();

    std::complex<float> actual_size = {
        parent->transform.scale.real() * size.real(),
        parent->transform.scale.imag() * size.imag(),

    };

if(IsKeyDown(KEY_LEFT)) parent->transform.position -= 0.1*2;
if(IsKeyDown(KEY_RIGHT)) parent->transform.position += 0.1*2;
if(IsKeyDown(KEY_DOWN)) parent->transform.position += std::complex<float>(0,1) * static_cast<float>(0.1*2);
LoadImage("/home/faisal/Documents/cpp-programming-tutor/week5/fatty.png");

DrawRectangle(parent->transform.position.real(), parent->transform.position.imag(), actual_size.imag(), actual_size.real() , Color(RED));


  }
};

}; // namespace pmall

int main() {
  pmall::Scene scene;
  scene.layers.emplace_back();

  auto rectangle = pmall::Entity::make();

  scene.layers.front().entites.emplace_back(rectangle);

  rectangle->Attach(std::make_shared<pmall::RectangleGizmoComponent>(128, 264));

  InitWindow(1200, 800, "test");

  rectangle->transform.position.real(128);
  rectangle->transform.position.imag(128);

  while (not WindowShouldClose()) {

    std::cout << rectangle->transform.position << "\n";
    BeginDrawing();

    ClearBackground(Color(WHITE));

    for (auto &layer : scene.layers) {
      layer.Draw();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
