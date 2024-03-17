
#include <algorithm>
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

  virtual void Draw() {}

  virtual void Update() {}
};

struct Transform {
  std::complex<float> position = {0, 0}; // position
  float angle = 0;
  std::complex<float> scale = {1, 1}; // size
};

struct Entity {

  Transform transform;
  std::vector<std::shared_ptr<Component>> components;

  std::vector<std::shared_ptr<Entity>> children;

  std::weak_ptr<Entity> parent;

  pmall::Transform absolute_transform() {
    auto p = parent.lock();
    if (not p)
      return transform;

    auto trans = p->absolute_transform();

    trans.position += transform.position;
    trans.angle += transform.angle;

    trans.scale = std::complex<float>{

        trans.scale.real() * transform.scale.real(),
        trans.scale.imag() * transform.scale.imag()

    };

    return trans;
  }

  static std::shared_ptr<Entity>
  make(std::shared_ptr<Entity> parent = nullptr) {
    auto entity = std::shared_ptr<Entity>(new Entity());
    entity->self = entity;
    if (parent) {
      entity->parent = parent;
      parent->children.emplace_back(entity);
    }
    return entity;
  }
  void Draw() {

    for (auto &enities : components) {

      enities->Draw();
    }

    for (auto &child : children) {

      child->Draw();
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
};

struct Scene {

  std::vector<Layer> layers;
};

struct RectangleGizmoComponent : public Component {
  std::complex<float> size;
  Color color;
  RectangleGizmoComponent(float width, float height, Color color)
      : size(width, height), color(color) {}

  void Draw() override {

    auto parent = owner.lock();

    auto abs_tr = parent->absolute_transform();

    std::complex<float> actual_size = {
        abs_tr.scale.real() * size.real(),
        abs_tr.scale.imag() * size.imag(),

    };

    DrawRectangle(abs_tr.position.real(), abs_tr.position.imag(),
                  actual_size.imag(), actual_size.real(), color);
  }
};

struct InputHairCross : public Component {

  InputHairCross() {}

  void Draw() override {

    auto parent = owner.lock();

    if (IsKeyDown(KEY_LEFT))
      parent->transform.position -= 0.1 * 2;
    if (IsKeyDown(KEY_RIGHT))
      parent->transform.position += 0.1 * 2;
    if (IsKeyDown(KEY_DOWN))
      parent->transform.position +=
          std::complex<float>(0, 1) * static_cast<float>(0.1 * 2);
    if (IsKeyDown(KEY_UP))
      parent->transform.position -=
          std::complex<float>(0, 1) * static_cast<float>(0.1 * 2);
  }
};

struct HairCrossComponent : public Component {

  HairCrossComponent() {}

  void Draw() override {

    auto parent = owner.lock();

    auto abs_tr = parent->absolute_transform();
    Texture2D image =
        LoadTexture("/home/faisal/Documents/cpp-programming-tutor/week5/"
                    "—Pngtree—crosshairs_6045892.png");

    DrawTexture(image, abs_tr.position.real(), abs_tr.position.imag(), BLACK);
  }
};

}; // namespace pmall

int main() {
  pmall::Scene scene;
  scene.layers.emplace_back();

  auto rectangle = pmall::Entity::make();

  auto haircross = pmall::Entity::make(rectangle);
  scene.layers.front().entites.emplace_back(rectangle);

  rectangle->Attach(
      std::make_shared<pmall::RectangleGizmoComponent>(128, 128, RED));

  haircross->Attach(std::make_shared<pmall::InputHairCross>());
  haircross->Attach(std::make_shared<pmall::HairCrossComponent>());

  InitWindow(1200, 800, "test");

  rectangle->transform.position = {128, 128};
  haircross->transform.position = {128, 128};
  while (not WindowShouldClose()) {

    std::cout << "Blue rectangle position" << rectangle->transform.position
              << "\n";
    std::cout << "haircross position" << haircross->transform.position << "\n";
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
