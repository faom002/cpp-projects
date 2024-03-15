#pragma once
#include <complex>

namespace pmall {
	struct Transform {
		std::complex<float> position = {0, 0};
		float angle = 0;
		std::complex<float> scale = {1, 1};
	};
}