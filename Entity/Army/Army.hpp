#ifndef ARMY_HPP
#define ARMY_HPP

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

    // Army:
    float stunned;
    int hp, hpMax;
    int atk;
    float coolDown;
    float speed, speedOri;
    float atkRadius;
    float detectRadius;
    Army(int id, int instanceID, float xB, float yB, std::string Name,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk);

    void Healed(float pt);
    void Damaged(float pt);
    
    void Draw() const override;
};

#endif // ARMY_HPP