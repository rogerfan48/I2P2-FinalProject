#ifndef MAINTOWER_HPP
#define MAINTOWER_HPP

#include "Tower.hpp"

class MainTower: public Tower {
public:
    static const int MainTowerMaxHp;
    static const float MainTowerCoolDown;
    // color: Blue/Red
    // x, y: left-up position
    MainTower(std::string color, float x, float y);
};

#endif // MAINTOWER_HPP