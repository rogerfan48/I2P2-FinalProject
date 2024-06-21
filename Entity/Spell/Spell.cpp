#include "Spell.hpp"
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>

#include "Engine/Point.hpp"
#include "Helper/Helper.hpp"
#include "Scene/PlayScene.hpp"

Spell::Spell(int id, int instanceID, float xB, float yB, std::string Name, 
        int pt, float radius, float duration, float interval, int atkTower, ALLEGRO_COLOR color): 
        IObject(xB, yB), ID(id), instanceID(instanceID), Name(Name), 
        pt(pt), radius(radius*PlayScene::BlockSize), time(duration), duration(duration), interval(interval), atkTower(atkTower), color(color) {
            Position = blockToPx(Engine::Point(xB, yB));
            Position.x += PlayScene::BlockSize/2;
            Position.y += PlayScene::BlockSize/2;
        }

void Spell::Draw() const {
    al_draw_filled_circle(Position.x, Position.y, radius, al_map_rgba(int(color.r*255), int(color.g*255), int(color.b*255), 80));
    al_draw_circle(Position.x, Position.y, radius-3, al_map_rgba(int(color.r*255), int(color.g*255), int(color.b*255), 200), 6);
}

void Spell::Update(float deltaTime) {
    time -= deltaTime;
    if (Name == "Zap") {
        
    } else if (Name == "Poison") {

    } else /* Heal */ {

    }
}