#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "MainTower.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int MainTower::MainTowerMaxHp = 4824;
const float MainTower::MainTowerCoolDown = 1.0;

MainTower::MainTower(std::string color, float x, float y) :
    Tower("tower/"+color+"MainTower.png", x, y, 4*PlayScene::BlockSize, 4*PlayScene::BlockSize, MainTowerMaxHp, MainTowerCoolDown) {
}