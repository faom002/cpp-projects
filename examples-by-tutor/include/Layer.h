#pragma once

#include <vector>
#include <memory>
#include "Entity.h"

namespace pmall {
	struct Layer {
		std::vector <std::shared_ptr<Entity>> entities;
		
		void Draw() {
			for (auto &entity: entities) {
				entity->Draw();
			}
		}
		
		void Update(float deltaTimeSeconds) {
			for (auto &entity: entities) {
				entity->Update(deltaTimeSeconds);
			}
		}
	};
}