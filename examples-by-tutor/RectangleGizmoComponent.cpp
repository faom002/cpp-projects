#include "Components/RectangleGizmo.h"
#include "raylib.h"

void pmall::RectangleGizmoComponent::Draw() {
	auto parent = owner.lock();
	auto abs_tr = parent->absolute_transform();
	std::complex<float> actual_size = {
		abs_tr.scale.real() * size.real(),
		abs_tr.scale.imag() * size.imag(),
	};
	DrawRectanglePro(
		Rectangle{
			abs_tr.position.real(),
			abs_tr.position.imag(),
			actual_size.real(),
			actual_size.imag()
		},
		Vector2{0, 0},
		abs_tr.angle * RAD2DEG,
	color
	);
}