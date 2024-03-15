#pragma once
#include <memory>

namespace pmall {
	struct Entity;
	
	struct Component {
		std::weak_ptr <Entity> owner;
		
		virtual void Draw() {}
		
		virtual void Update(float deltaTimeSeconds) {}
	};
}