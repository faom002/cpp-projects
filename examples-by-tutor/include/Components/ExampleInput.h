#pragma once

#include "../Component.h"
#include "../Entity.h"
#include "../Transform.h"
#include "raylib.h"
#include <complex>

namespace pmall {
	struct ExampleInputComponent : public Component {
        ExampleInputComponent()
		{}
		
		void Update(float seconds) override;
	};
}
