#ifndef TOWER_HPP
#define TOWER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Enemy;
class PlayScene;

class Tower: public Engine::Image {
protected:
    int hp, max_hp;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Tower*>::iterator lockedTowerIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    // virtual void CreateBullet() = 0;

public:
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Tower(std::string imgTower, float x, float y, float w, float h, int hp, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif 
