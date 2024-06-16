#ifndef TOWER_HPP
#define TOWER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"

class Tower: public Engine::Image {
protected:
    float maxHp;
    float CoolDown;
    PlayScene* getPlayScene();
    ALLEGRO_COLOR bloodColor = al_map_rgb(0, 255, 0), textColor = al_map_rgb(255, 255, 255);
public:
    float hp;
    bool enabled = true;
    std::string color;
    // Army* target = nullptr;
    Tower(std::string imgTower, float x, float y, float w, float h, int hp, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // TOWER_HPP