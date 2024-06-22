#ifndef TOWER_HPP
#define TOWER_HPP

#include <allegro5/color.h>
#include "Entity/Army/Army.hpp"

class Tower: public Army {
protected:
    ALLEGRO_COLOR redCdColor = al_map_rgb(255, 160, 40);
    ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR Black = al_map_rgb(0, 0, 0);
    std::shared_ptr<ALLEGRO_BITMAP> towerImage;
    std::shared_ptr<ALLEGRO_BITMAP> sleepTowerImage;
public:
    bool enabled;
    Tower(int id, int instanceID, float xB, float yB, int hp, int atk, float cd, float atkRadius, float picRadiusBk, int faction, bool enabled=true);
    void Draw() const override;
};

#endif // TOWER_HPP