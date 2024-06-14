#include "LoadScene.hpp"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/RectangleButton.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"

void LoadScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::RectangleButton* btn;
    int diff[3] = {120, 250, 380};
    int labelDiff = 50;
    ALLEGRO_COLOR bgColor = al_map_rgb(5, 0, 20);
    ALLEGRO_COLOR btnColor = al_map_rgb(150, 90, 15);
    ALLEGRO_COLOR btnColorHovered = al_map_rgb(200, 140, 70);

    AddNewObject(new Engine::Rectangle(0, 0, w, h, bgColor));
    AddNewObject(new Engine::Label("Arena Legends", "recharge.otf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW - 250, halfH / 2 + diff[0] , 500, 100, btnColor, btnColorHovered);
    // btn = new Engine::RectangleButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 250, halfH / 2 + diff[0] , 500, 100);
    btn->SetOnClickCallback(std::bind(&LoadScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Play", "recharge.otf", 48, halfW, halfH / 2 + diff[0] + labelDiff, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW - 250, halfH / 2 + diff[1] , 500, 100, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LoadScene::ScoreboardOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Scoreboard", "recharge.otf", 48, halfW, halfH / 2 + diff[1] + labelDiff, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW - 250, halfH / 2 + diff[2], 500, 100, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LoadScene::SettingsOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "recharge.otf", 48, halfW, halfH / 2 + diff[2] + labelDiff, 0, 0, 0, 255, 0.5, 0.5));
}
void LoadScene::Terminate() {
    IScene::Terminate();
}
void LoadScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("load");
}
void LoadScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("load");
}
void LoadScene::ScoreboardOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("load");
}