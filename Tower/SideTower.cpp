#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "SideTower.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int SideTower::SideTowerMaxHp = 3052;
const float SideTower::SideTowerCoolDown = 0.8;

SideTower::SideTower(std::string color, float x, float y) :
    Tower("tower/"+color+"SideTower.png", x, y, 3*PlayScene::BlockSize, 3*PlayScene::BlockSize, SideTowerMaxHp, SideTowerCoolDown) {
        Tower::color = color;
}