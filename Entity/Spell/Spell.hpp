#ifndef SPELL_HPP
#define SPELL_HPP

#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

class Spell: public Engine::IObject, public Engine::IControl {
protected:
    GameData& gameData = Engine::GameEngine::GetInstance().data;
public:
    int ID;
    int instanceID;
    std::string Name;
    std::string Description;
    std::shared_ptr<ALLEGRO_BITMAP> head;
    ALLEGRO_COLOR color;
    bool ready;
    float readyFlash;

    // Spell:
    int pt;    // atk or heal
    int atkTower;
    float radius;
    float time, duration;
    float span, interval;
    Spell(int id, int instanceID, float xB, float yB, std::string Name, 
        int pt, float radius, float duration, float interval, int atkTower, ALLEGRO_COLOR color);

    void Draw() const override;
    void Update(float deltaTime) override;
};

#endif // SPELL_HPP