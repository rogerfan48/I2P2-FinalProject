#ifndef TOWER_HPP
#define TOWER_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

class Tower: public Army {
protected:
    ALLEGRO_COLOR blueBlood = al_map_rgb(0, 180, 255);
    ALLEGRO_COLOR redBlood = al_map_rgb(255, 100, 100);
    ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR Black = al_map_rgb(0, 0, 0);
    std::shared_ptr<ALLEGRO_BITMAP> towerImage;
    std::shared_ptr<ALLEGRO_BITMAP> sleepTowerImage;
public:
    bool enabled;
    Tower(int id, int instanceID, float xB, float yB, int hp, int atk, float cd, float atkRadius, float picRadiusBk, int faction, bool enabled=true);
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // TOWER_HPP