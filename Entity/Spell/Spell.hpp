#ifndef SPELL_HPP
#define SPELL_HPP

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

    // Spell:
    int pt;    // atk or heal
    int atkTower;
    float radius;
    float duration;
    float interval;
    Spell(bool selected, int id, float x, float y, std::string Name, std::string Description, int pt, float radius, float duration, float interval, int atkTower, int cost);
    Spell(int id, float x, float y, std::string Name, int pt, float radius, float duration, float interval, int atkTower, int cost);

    void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
};

#endif // SPELL_HPP