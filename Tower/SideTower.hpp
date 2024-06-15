#ifndef SIDETOWER_HPP
#define SIDETOWER_HPP
#include "Tower.hpp"

class SideTower: public Tower {
public:
    // color 第一個字母要大寫, ex : Blue
    SideTower(std::string color, float x, float y);
    // void CreateBullet() override;
};
#endif
