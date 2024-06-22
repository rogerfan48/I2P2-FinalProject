#include "Helper.hpp"
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#include <cmath>
#include <string>

#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"

std::string floatToStr(float num) {
    char buffer[10];
    std::snprintf(buffer, sizeof(buffer), "%.1f", num);
    return std::string(buffer);
}

Engine::Point pxToBlock(const Engine::Point& px) {
    return Engine::Point(int(px.x/PlayScene::BlockSize)-2, int(px.y/PlayScene::BlockSize)-2);
}
Engine::Point blockToPx(const Engine::Point& block) {
    return Engine::Point((block.x+2)*PlayScene::BlockSize, (block.y+2)*PlayScene::BlockSize);
}
Engine::Point blockToMiddlePx(const Engine::Point& block) {
    return Engine::Point((block.x+2.5)*PlayScene::BlockSize, (block.y+2.5)*PlayScene::BlockSize);
}

std::string timeString(float sec) {
    if (int(sec)%60 < 10) return std::to_string(int(sec)/60)+" : 0"+std::to_string(int(sec)%60);
    else return std::to_string(int(sec)/60)+" : "+std::to_string(int(sec)%60);
}

double findAngle(Engine::Point center, Engine::Point point) {
    if (center.y >= point.y) 
        return std::acos((point.x - center.x) / (center - point).Magnitude());
    else
        return std::acos((center.x - point.x) / (center - point).Magnitude()) + ALLEGRO_PI;
}

// 0: blue, 1: bridge, 2: red
int whichSide(Engine::Point pos) {
    Engine::Point nB = pxToBlock(pos);
    if (nB.x > 16) return 0;
    else if (nB.x < 15) return 2;
    else return 1;
}