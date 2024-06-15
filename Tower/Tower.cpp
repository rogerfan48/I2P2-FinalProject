#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>

#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/Image.hpp"
#include "Tower.hpp"

PlayScene* Tower::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Tower::Tower(std::string imgTower, float x, float y, float w, float h, int hp, float coolDown) :
	Image(imgTower, x, y, w, h, 0, 0), hp(hp), max_hp(hp), coolDown(coolDown) {}
void Tower::Update(float deltaTime) {
	PlayScene* scene = getPlayScene();
	// if (!Enabled)
	// 	return;
	// if (Target) {
	// 	Engine::Point diff = Target->Position - Position;
	// 	if (diff.Magnitude() > CollisionRadius) {
	// 		Target->lockedTowers.erase(lockedTowerIterator);
	// 		Target = nullptr;
	// 		lockedTowerIterator = std::list<Tower*>::iterator();
	// 	}
	// }
	// if (!Target) {
	// 	// Lock first seen target.
	// 	// Can be improved by Spatial Hash, Quad Tree, ...
	// 	// However simply loop through all enemies is enough for this program.
	// 	for (auto& it : scene->EnemyGroup->GetObjects()) {
	// 		Engine::Point diff = it->Position - Position;
	// 		if (diff.Magnitude() <= CollisionRadius) {
	// 			Target = dynamic_cast<Enemy*>(it);
	// 			Target->lockedTowers.push_back(this);
	// 			lockedTowerIterator = std::prev(Target->lockedTowers.end());
	// 			break;
	// 		}
	// 	}
	// }
	// if (Target) {
	// 	Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	// 	Engine::Point targetRotation = (Target->Position - Position).Normalize();
	// 	float maxRotateRadian = rotateRadian * deltaTime;
	// 	float cosTheta = originRotation.Dot(targetRotation);
	// 	// Might have floating-point precision error.
	// 	if (cosTheta > 1) cosTheta = 1;
	// 	else if (cosTheta < -1) cosTheta = -1;
	// 	float radian = acos(cosTheta);
	// 	Engine::Point rotation;
	// 	if (abs(radian) <= maxRotateRadian)
	// 		rotation = targetRotation;
	// 	else
	// 		rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
	// 	// Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
	// 	Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
	// 	// Shoot reload.
	// 	reload -= deltaTime;
	// 	if (reload <= 0) {
	// 		// shoot.
	// 		reload = coolDown;
	// 		CreateBullet();
	// 	}
	// }
}
void Tower::Draw() const {
	Image::Draw();
    al_draw_rectangle(Position.x, Position.y-40, 
			Position.x+Size.x, Position.y-20, al_map_rgb(255,255,255),10);
	al_draw_filled_rectangle(Position.x, Position.y-40, 
            Position.x+hp/max_hp*Size.x, Position.y-20, al_map_rgb(0,255,0));
}
