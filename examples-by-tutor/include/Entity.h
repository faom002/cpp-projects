#pragma once

#include "Transform.h"
#include "Component.h"
#include <vector>
#include <memory>

namespace pmall {
	struct Entity {
		pmall::Transform transform;
		std::vector<std::shared_ptr<Entity>> children;
		std::weak_ptr<Entity> parent;
		
		pmall::Transform absolute_transform() {
			constexpr auto i = std::complex<float>(0, 1);
			auto p = parent.lock();
			if(not p) return transform;
			
			auto trans = p->absolute_transform();
			auto rotated_vector = std::complex<float>{
				std::cos(trans.angle),
				std::sin(trans.angle)
			};
			auto local_vector = transform.position;
			auto unscaled_rotation = local_vector * rotated_vector;
			trans.position +=
				unscaled_rotation.real() * trans.scale.real()
				+ i*unscaled_rotation.imag() * trans.scale.imag();
			trans.angle += transform.angle;
			trans.scale = std::complex<float>{
				trans.scale.real() * transform.scale.real(),
				trans.scale.imag() * transform.scale.imag()
			};
			return trans;
		}
		
		void Draw() {
			for (auto &component: components) {
				component->Draw();
			}
			for (auto &child: children) {
				child->Draw();
			}
		}
		
		void Update(float deltaTimeSeconds) {
			// We regulate the angle between 0 <= 𝜃 <= 2𝜋
			while(transform.angle < 0) transform.angle += 2*std::numbers::pi_v<float>;
			while(transform.angle > 2*std::numbers::pi_v<float>) transform.angle -= 2*std::numbers::pi_v<float>;
			for (auto &component: components) {
				component->Update(deltaTimeSeconds);
			}
			for (auto &child: children) {
				child->Update(deltaTimeSeconds);
			}
		}
		
		static std::shared_ptr<Entity> make(std::shared_ptr<Entity> parent = nullptr) {
			auto entity = std::shared_ptr<Entity>(new Entity());
			entity->self = entity;
			if(parent) {
				entity->parent = parent;
				parent->children.emplace_back(entity);
			}
			return entity;
		}
		
		void Attach(std::shared_ptr<Component> component) {
			if (component->owner.lock()) throw std::runtime_error("Component already attached");
			component->owner = self;
			components.emplace_back(component);
		}
	
	private:
		std::vector<std::shared_ptr<Component>> components;
		std::weak_ptr<Entity> self;
		
		Entity() {}
	};
}