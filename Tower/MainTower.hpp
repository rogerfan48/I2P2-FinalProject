#ifndef MAINTOWER_HPP
#define MAINTOWER_HPP
#include "Tower.hpp"

class MainTower: public Tower {
public:
    // color 第一個字母要大寫, ex : Blue
    MainTower(std::string color, float x, float y);
    // void CreateBullet() override;
};
#endif
