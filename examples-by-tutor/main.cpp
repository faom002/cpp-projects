#include "include/Components/ExampleInput.h"
#include "include/Components/RectangleGizmo.h"
#include "include/Entity.h"
#include "include/Scene.h"
#include "raylib.h"
#include <iostream>

int main() {
	pmall::Scene scene;
	scene.layers.emplace_back();
	
	auto entity = pmall::Entity::make();
	auto entity2 = pmall::Entity::make(entity);
	
	scene.layers.front().entities.emplace_back(entity);
	
	entity->Attach(std::make_shared<pmall::RectangleGizmoComponent>(128, 64, BLUE));
	entity->Attach(std::make_shared<pmall::ExampleInputComponent>());
	entity2->Attach(std::make_shared<pmall::RectangleGizmoComponent>(64, 64, RED));
	
	InitWindow(800,600, "Pmall");
	
	entity->transform.position.real(128);
	entity->transform.position.imag(128);
	entity2->transform.position.real(128);
	entity2->transform.position.imag(128);
	
	while(not WindowShouldClose()) {
		float frameTime = GetFrameTime();
		for(auto& layer : scene.layers) {
			layer.Update(frameTime);
		}
		BeginDrawing();
		ClearBackground(WHITE);
		for(auto& layer : scene.layers) {
			layer.Draw();
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
