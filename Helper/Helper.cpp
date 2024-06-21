#include "Helper.hpp"
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#include <cmath>

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

double findAngle(Engine::Point center, Engine::Point point) {
    if (center.y <= point.y) 
        return acos((point.x - center.x) / (center - point).Magnitude());
    else
        return acos((center.x - point.x) / (center - point).Magnitude()) + ALLEGRO_PI;
}