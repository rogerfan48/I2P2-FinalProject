#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "SideTower.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

static int const sideTower_max_hp = 3052;
SideTower::SideTower(std::string color, float x, float y) :
	Tower("tower/"+color+"SideTower.png", x, y, 
        3*PlayScene::BlockSize, 3*PlayScene::BlockSize, sideTower_max_hp, 1) {
}
