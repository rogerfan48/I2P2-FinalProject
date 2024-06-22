#ifndef SIDETOWER_HPP
#define SIDETOWER_HPP

#include "Tower.hpp"

class SideTower: public Tower {
public:
    static const int SideTowerMaxHp;
    static const int SideTowerAtk;
    static const float SideTowerCoolDown;

    SideTower(int id, int instanceID, float xB, float yB, int faction);
};

#endif // SIDETOWER_HPP