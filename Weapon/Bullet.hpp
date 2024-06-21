#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"
#include "Entity/Army/Army.hpp"

class Bullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	PlayScene* getPlayScene();
	virtual void OnExplode();
public:
	Army* target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Army* target);
	void Update(float deltaTime) override;
};
#endif // BULLET_HPP
