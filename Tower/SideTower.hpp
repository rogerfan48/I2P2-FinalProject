#ifndef SIDETOWER_HPP
#define SIDETOWER_HPP

#include "Tower.hpp"

class SideTower: public Tower {
public:
    static const int SideTowerMaxHp;
    static const float SideTowerCoolDown;
    // color: Blue/Red
    // x, y: left-up position
    SideTower(std::string color, float x, float y);
};

#endif // SIDETOWER_HPP