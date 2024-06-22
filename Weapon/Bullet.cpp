#include <cmath>
#include "Bullet.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Helper/Helper.hpp"

Bullet::Bullet(std::string img, float speed, float damage, float x, float y, float w, float h, Army* target, bool isRange) :
	Sprite(img, x, y, w, h), speed(speed), damage(damage), target(target), isRange(isRange) {
	Rotation = findAngle(Position, target->Position);
	Velocity.x = cos(Rotation) * speed, Velocity.y = sin(Rotation) * speed * (-1);
	CollisionRadius = 25;
}

void Bullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
	if (!target) {
		static float tick = 255;
		tick -= deltaTime;
		if (tick > 0) {
			Tint = al_map_rgba(255, 255, 255, tick);
		} else {
			PS->WeaponGroup->RemoveObject(objectIterator);
		}
		return;
	}
	Rotation = findAngle(Position, target->Position);
	Velocity.x = cos(Rotation) * speed;
	Velocity.y = sin(Rotation) * speed * (-1);
	if ((Position - target->Position).Magnitude() <= CollisionRadius) {
		OnExplode();
		target->Damaged(damage);
		PS->WeaponGroup->RemoveObject(objectIterator);
		return;
	}
}

void Bullet::OnExplode() {
	//
}