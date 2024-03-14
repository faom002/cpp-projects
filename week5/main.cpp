
#include <raylib.h>
#include <complex>
#include <memory>
#include <vector>

namespace pmall {

struct Entity;

struct Component {

  std::weak_ptr<Entity> owner;

  virtual void Draw(){};

  virtual void Update(){};
};


struct Transform {
    std::complex<float> position {0,0};
    std::complex<float> scale;
    std::complex<float> size {1,1};

};

struct Entity {

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

  void Attach(std::shared_ptr<Component> component) {

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

    void Draw() override {

        DrawRectangle(1200/2, 800/2, 500, 500, Color(RED));

    }


};


}; // namespace pmall

int main() {
    pmall::Scene scene;
    scene.layers.emplace_back();

    auto rectangle = pmall::Entity::make();

    scene.layers.front().entites.emplace_back(rectangle);


    rectangle->Attach(std::make_shared<pmall::RectangleGizmoComponent>());

    InitWindow(1200, 800, "test");


    while(not WindowShouldClose()){

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
