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
    ALLEGRO_COLOR bgColor = al_map_rgb(5, 0, 20);
    ALLEGRO_COLOR btnColor = al_map_rgb(150, 90, 15);
    ALLEGRO_COLOR btnColorHovered = al_map_rgb(200, 140, 70);

    AddNewObject(new Engine::Rectangle(0, 0, w, h, bgColor));
    AddNewObject(new Engine::Label("Arena Legends", "recharge.otf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    Engine::Image* btn = new Engine::Image("turtle.jpg", halfW - 300, halfH - 200, 600, 600, 0, 0);
    AddNewObject(btn);
    AddNewObject(new Engine::Label("Loading . . .", "recharge.otf", 64, halfW, halfH + 500, 255, 255, 255, 255, 0.5, 0.5));
}
void LoadScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    tick += deltaTime;
    if (tick >= 3) {
        tick = 0;
        Engine::GameEngine::GetInstance().ChangeScene("lobby");
    }
}
void LoadScene::Terminate() {
    IScene::Terminate();
}