#include "LobbyScene.hpp"
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

void LobbyScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::RectangleButton* btn;

    const int initH = 50;
    const int labelW = 900;
    const int labelH = 120;
    const int lhc = 150;
    const int lhp = 250;    // labelHPlay
    const int padding = 30;
    const int diff[4] = {initH, initH+lhc+padding, initH+lhc+lhp+padding*2, initH+lhc+lhp+labelH+padding*3};

    const ALLEGRO_COLOR bgColor = al_map_rgb(5, 0, 20);
    const ALLEGRO_COLOR btnColor = al_map_rgb(170, 90, 30);
    const ALLEGRO_COLOR btnColorHovered = al_map_rgb(200, 140, 70);

    AddNewObject(new Engine::Rectangle(0, 0, w, h, bgColor));
    AddNewObject(new Engine::Label("Arena Legends", "recharge.otf", 140, halfW, halfH/3, 10, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW-labelW/2, halfH/2+diff[0], labelW, lhc, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LobbyScene::ScoreboardOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Card Set", "recharge.otf", 60, halfW, halfH/2+diff[0]+lhc/2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW-labelW/2, halfH/2+diff[1], (labelW-padding)/2, lhp, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LobbyScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Single", "recharge.otf", 60, halfW-(labelW+padding)/4-36, halfH/2+diff[1]+lhp/2-36, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Battle", "recharge.otf", 60, halfW-(labelW+padding)/4+36, halfH/2+diff[1]+lhp/2+36, 0, 0, 0, 255, 0.5, 0.5));
    btn = new Engine::RectangleButton(halfW+padding/2, halfH/2+diff[1], (labelW-padding)/2, lhp, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LobbyScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Online", "recharge.otf", 60, halfW+(labelW+padding)/4-36, halfH/2+diff[1]+lhp/2-36, 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Battle", "recharge.otf", 60, halfW+(labelW+padding)/4+36, halfH/2+diff[1]+lhp/2+36, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW-labelW/2, halfH/2+diff[2], labelW, labelH, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LobbyScene::ScoreboardOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Scoreboard", "recharge.otf", 52, halfW, halfH/2+diff[2]+labelH/2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(halfW-labelW/2, halfH/2+diff[3], labelW, labelH, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&LobbyScene::SettingsOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "recharge.otf", 52, halfW, halfH/2+diff[3]+labelH/2, 0, 0, 0, 255, 0.5, 0.5));
}
void LobbyScene::Terminate() {
    IScene::Terminate();
}
void LobbyScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("lobby");
}
void LobbyScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("load");
}
void LobbyScene::ScoreboardOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("load");
}