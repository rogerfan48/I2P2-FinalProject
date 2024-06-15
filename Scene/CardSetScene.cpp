#include "Scene/CardSetScene.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/RectangleButton.hpp"
#include "UI/Component/Label.hpp"

void CardSetScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::RectangleButton* btn;

    const ALLEGRO_COLOR bgColor = al_map_rgb(5, 0, 20);
    const ALLEGRO_COLOR btnColor = al_map_rgb(170, 90, 30);
    const ALLEGRO_COLOR btnColorHovered = al_map_rgb(200, 140, 70);

    AddNewObject(new Engine::Rectangle(0, 0, w, h, bgColor));
    AddNewObject(new Engine::Label("Card Set: Select Exactly 8 Cards", "recharge.otf", 60, halfW, 100, 255, 255, 255, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(300, 1250, 500, 100, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&CardSetScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "recharge.otf", 52, 550, 1300, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::RectangleButton(1000, 1250, 500, 100, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&CardSetScene::CheckOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Check", "recharge.otf", 52, 1250, 1300, 0, 0, 0, 255, 0.5, 0.5));
}
void CardSetScene::Terminate() {
    IScene::Terminate();
}
void CardSetScene::CheckOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("lobby");
}
void CardSetScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("lobby");
}