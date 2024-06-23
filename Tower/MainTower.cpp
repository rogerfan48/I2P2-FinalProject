#include "MainTower.hpp"

#include "Engine/Resources.hpp"

const int MainTower::MainTowerMaxHp = 4824;
const int MainTower::MainTowerAtk = 109;
const float MainTower::MainTowerCoolDown = 1;

MainTower::MainTower(int id, int instanceID, float xB, float yB, int faction):
    Tower(id, instanceID, xB, yB, MainTowerMaxHp, MainTowerAtk, MainTowerCoolDown, 9, 2, faction, false) {
        if (faction) {
            towerImage = Engine::Resources::GetInstance().GetBitmap("tower/RedMainTower.png");
            sleepTowerImage = Engine::Resources::GetInstance().GetBitmap("tower/RedSleepMainTower.png");
        } else {
            towerImage = Engine::Resources::GetInstance().GetBitmap("tower/BlueMainTower.png");
            sleepTowerImage = Engine::Resources::GetInstance().GetBitmap("tower/BlueSleepMainTower.png");
        }
    }