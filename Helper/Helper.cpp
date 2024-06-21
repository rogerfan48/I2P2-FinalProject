#include "Helper.hpp"
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