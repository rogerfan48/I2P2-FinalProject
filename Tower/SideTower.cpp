#include "SideTower.hpp"

const int SideTower::SideTowerMaxHp = 3052;
const int SideTower::SideTowerAtk = 109;
const float SideTower::SideTowerCoolDown = 0.8;

SideTower::SideTower(int id, int instanceID, float xB, float yB, int faction):
    Tower(id, instanceID, xB, yB, SideTowerMaxHp, SideTowerAtk, SideTowerCoolDown, 7.5, 1.5, faction) {
        if (faction) {
            towerImage = Engine::Resources::GetInstance().GetBitmap("tower/RedSideTower.png");
        } else {
            towerImage = Engine::Resources::GetInstance().GetBitmap("tower/BlueSideTower.png");
        }
    }