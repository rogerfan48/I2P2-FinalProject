#ifndef ARMY_HPP
#define ARMY_HPP

#include <set>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

class Army: public Engine::IObject {
protected:
    GameData& gameData = Engine::GameEngine::GetInstance().data;
public:
    int ID;
    int instanceID;
    std::string Name;
    std::string Description;
    std::shared_ptr<ALLEGRO_BITMAP> head;
    float picRadiusPx;

    std::set<Army*> beTargeted;
    Army* target;

    // Army:
    bool fireBullet;    // := Not Melee
    float stunned;
    int hp, hpMax;
    int atk;
    float countDown, coolDown;
    float speed, speedOri;
    float atkRadius;
    float detectRadius;
    Army(int id, int instanceID, float xB, float yB, std::string Name,
        bool bullet, int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk);

    void Draw() const override;
    void Update(float deltaTime) override;
    
    void Healed(float pt);
    void Damaged(float pt);
    Army* searchTarget();
};

#endif // ARMY_HPP