#ifndef MAINTOWER_HPP
#define MAINTOWER_HPP

#include "Tower.hpp"

class MainTower: public Tower {
public:
    static const int MainTowerMaxHp;
    static const int MainTowerAtk;
    static const float MainTowerCoolDown;

    MainTower(int id, int instanceID, float xB, float yB, int faction);
};

#endif // MAINTOWER_HPP