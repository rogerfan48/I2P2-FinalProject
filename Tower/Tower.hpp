#ifndef TOWER_HPP
#define TOWER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"

class Tower: public Engine::Image {
protected:
    int hp, maxHp;
    float CoolDown;
    PlayScene* getPlayScene();

public:
    bool enabled = true;
    // Army* target = nullptr;
    Tower(std::string imgTower, float x, float y, float w, float h, int hp, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // TOWER_HPP