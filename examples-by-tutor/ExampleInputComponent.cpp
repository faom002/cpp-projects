#include "Components/ExampleInput.h"

void pmall::ExampleInputComponent::Update(float seconds) {
	auto parent = owner.lock();
	constexpr auto i = std::complex<float>(0, 1);
	const float speed = 150.0f;
	parent->transform.position += seconds * speed * (IsKeyDown(KEY_RIGHT) ? 1.0f : 0.0f);
	parent->transform.position -= seconds * speed * (IsKeyDown(KEY_LEFT) ? 1.0f : 0.0f);
	if (IsKeyDown(KEY_DOWN)) {
		parent->transform.position += i * seconds * speed;
	}
	if (IsKeyDown(KEY_UP)) {
		parent->transform.position -= i * seconds * speed;
	}
	parent->transform.angle += seconds * 15.0f * (IsKeyDown(KEY_L) ? 1.0f : 0.0f);
}