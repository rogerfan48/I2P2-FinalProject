#ifndef ARMY_HPP
#define ARMY_HPP

#include <set>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

enum Direction{U, D, L, R, UL, UR, DL, DR, NON};
static Direction map[18][32] = {
    {DR,DR,DR, D, D, D,DL,DL,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D, D, D,DL,DL,DL,DL,DL,DL,DL,DL, L, L, L, L},
    {DR,DR,DR, D, D,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D, D,DL,DL,DL,DL,DL, L, L, L, L, L, L, L, L},
    {DR,DR,DR, D,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D,DL,DL,DL,DL,DL,DL,DL,UL,UL,UL, L, L, L, L},
    {DR,DR,DR, D, L, L, L, L, L, L, L, L, L, L, L,  L, L,  L, L, L, L, L, L, L, L, L, R, U, L, L, L, L},
    {DR,DR,DR, D, L,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U,UL,UL,UL,UL,UL,UL,UL,DL,DL,DL, L, L, L, L},
    {DR,DR,DR, D, L, L,DL,UL,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U, U,UL,UL,UL,UL,UL, L, L, L, L, L, L, L, L},
    {DR,DR,DR, D, L, L, L,UL,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U, U, U,UL,UL,UL,UL,UL,UL,UL,UL, L, L, L, L},
    { R,DR,DR, D, L, L, L, L,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U, U, U, U,UL,UL,UL,UL,UL,UL, L, U, U, U, U},
    { R,DR,DR, D, L, L, L, L, L,UL,UL,UL,UL,UL,UL, UL,UR,  U, U, U, U, U,UL,UL,UL,UL,UL, L, U, U, U, U},
    // -----------------------------------------------------------------------------------------------//
    { R,UR,UR, U, L, L, L, L, L,DL,DL,DL,DL,DL,DL, DL,DR,  D, D, D, D, D,DL,DL,DL,DL,DL, L, D, D, D, D},
    { R,UR,UR, U, L, L, L, L,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D, D, D, D,DL,DL,DL,DL,DL,DL, L, D, D, D, D},
    {UR,UR,UR, U, L, L, L,DL,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D, D, D,DL,DL,DL,DL,DL,DL,DL,DL, L, L, L, L},
    {UR,UR,UR, U, L, L,UL,DL,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D, D,DL,DL,DL,DL,DL, L, L, L, L, L, L, L, L},
    {UR,UR,UR, U, L,DL,DL,DL,DL,DL,DL,DL,DL,DL,DL, DL,DR,  D,DL,DL,DL,DL,DL,DL,DL,UL,UL,UL, L, L, L, L},
    {UR,UR,UR, U, L, L, L, L, L, L, L, L, L, L, L,  L, L,  L, L, L, L, L, L, L, L, L, R, D, L, L, L, L},
    {UR,UR,UR, U,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U,UL,UL,UL,UL,UL,UL,UL,DL,DL,DL, L, L, L, L},
    {UR,UR,UR, U, U,UL,UL,UL,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U, U,UL,UL,UL,UL,UL, L, L, L, L, L, L, L, L},
    {UR,UR,UR, U, U, U,UL,UL,UL,UL,UL,UL,UL,UL,UL, UL,UR,  U, U, U,UL,UL,UL,UL,UL,UL,UL,UL, L, L, L, L},
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
    Army* searchTarget();
};

#endif // ARMY_HPP