#ifndef ARMY_HPP
#define ARMY_HPP

#include <set>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

enum Direction{U, D, L, R, UL, UR, DL, DR, NON};
static Direction map[18][32] = {
    {DR,DR,DR,DR,DR, D, D, D,DL,DL,DL,DL,DL,DL,DL,DL,DR, D,DL,DL,DL,DL,DL,DL,DL,DL,DL, L, L, L, L, L},
    {DR,DR,DR,DR,DR, D, D, D,DL,DL,DL,DL,DL,DL,DL,DL,DR, D,DL,DL,DL,DL,DL, D, L, L, L, L, L, L, L, L},
    {DR,DR,DR, D,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL, D,DL,DL,DL,DL,DL, D,DL, L, L, U, L, L, L, L},
    {DR,DR,DR, D, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, U, L, L, L, L},
    {DR,DR,DR, D,DL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL, U,UL, L,DL, D, L, L, L, L},
    {DR,DR,DR, D,DL,DL,DL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UR, U,UL,UL,UL,UL,UL,UL,UL, L, L, L, L, L, L, L},
    {DR,DR,DR, D,DL,DL,DL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UR, U,UL,UL,UL,UL,UL,UL,UL,UL,UL, L, L, L, L, L},
    {DR,DR,DR, D,DL,DL,DL,DL,UL,UL,UL,UL,UL,UL,UL,UL,UR, U,UL,UL,UL,UL,UL,UL,UL,UL,UL, L, L, L, L, U},
    {DR,DR,DR, D, L, L, L, L, L,UL,UL,UL,UL,UL,UL,UL,UR, U,UL,UL,UL,UL,UL,UL,UL,UL,UL, L, L, L, L, U},
    // -----------------------------------------------------------------------------------------------
    {UR,UR,UR, U, L, L, L, L, L,DL,DL,DL,DL,DL,DL,DL,DR, D,DL,DL,DL,DL,DL,DL,DL,DL,DL, L, L, L, L, D},
    {UR,UR,UR, U,UL,UL,UL,UL,DL,DL,DL,DL,DL,DL,DL,DL,DR, D,DL,DL,DL,DL,DL,DL,DL,DL,DL, L, L, L, L, D},
    {UR,UR,UR, U,UL,UL,UL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DR, D,DL,DL,DL,DL,DL,DL,DL,DL,DL, L, L, L, L, L},
    {UR,UR,UR, U,UL,UL,UL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DR, D,DL,DL,DL,DL,DL,DL,DL, L, L, L, L, L, L, L},
    {UR,UR,UR, U,UL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL, D,DL, L,UL, U, L, L, L, L},
    {UR,UR,UR, U, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, L, D, L, L, L, L},
    {UR,UR,UR, U,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL, U,UL,UL,UL,UL,UL, U,UL, L, L, D, L, L, L, L},
    {UR,UR,UR,UR,UR, U, U, U,UL,UL,UL,UL,UL,UL,UL,UL,UR, U,UL,UL,UL,UL,UL, U, L, L, L, L, L, L, L, L},
    {UR,UR,UR,UR,UR, U, U, U,UL,UL,UL,UL,UL,UL,UL,UL,UR, U,UL,UL,UL,UL,UL,UL,UL,UL,UL, L, L, L, L, L},
};
class Army: public Engine::IObject {
protected:
    GameData& gameData = Engine::GameEngine::GetInstance().data;
public:
    int ID;
    int instanceID;
    int faction;    // 0 for blue, 1 for red
    bool isTower;
    std::string Name;
    std::string Description;
    std::shared_ptr<ALLEGRO_BITMAP> head;
    float picRadiusPx;
    int side;       // 0: blue, 1: bridge, 2: red

    std::set<Army*> beTargeted;
    Army* target;

    // Army:
    bool fireBullet;    // := Not Melee
    float stunned;
    float hp, hpMax;
    int atk;
    float countDown, coolDown;
    float speed, speedOri;
    float atkRadius;
    float detectRadius;
    Army(int id, int instanceID, float xB, float yB, std::string Name,
        bool bullet, int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk, int faction=0, bool isTower=false);

    void Draw() const override;
    void Update(float deltaTime) override;
    
    void Healed(float pt);
    void Damaged(float pt);
    void towardWhere();
    void go(bool mirror = false);
    void goToBridge();
    void goToTower();
    Army* searchTarget();
};

#endif // ARMY_HPP