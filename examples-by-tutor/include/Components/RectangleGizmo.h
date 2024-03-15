#pragma once

#include "../Component.h"
#include "../Transform.h"
#include "../Entity.h"
#include <complex>
#include "raylib.h"

namespace pmall {
	struct RectangleGizmoComponent : public Component {
		std::complex<float> size;
		Color color = RED;
		
		RectangleGizmoComponent(float width, float height, Color color = RED)
			: size(width, height), color(color) {}
		
		void Draw() override;
	};
}
