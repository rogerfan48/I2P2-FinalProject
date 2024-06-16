#include "LoadScene.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/Rectangle.hpp"
#include "UI/Component/Label.hpp"

Engine::Image* turtle;
void LoadScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    halfW = w / 2;
    halfH = h / 2;
    ALLEGRO_COLOR bgColor = al_map_rgb(5, 0, 20);

    AddNewObject(new Engine::Rectangle(0, 0, w, h, bgColor));
    AddNewObject(new Engine::Label("Arena Legends", "recharge.otf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));

    turtle = new Engine::Image("loading/1.jpg", halfW - 504, halfH - 200, 1008, 567, 0, 0);
    AddNewObject(turtle);
    AddNewObject(new Engine::Label("Loading . . .", "recharge.otf", 64, halfW, halfH + 500, 255, 255, 255, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("turtle.ogg", true, AudioHelper::BGMVolume);
}
void LoadScene::Update(float deltaTime) {
    IScene::Update(deltaTime);
    tick += deltaTime;
    RemoveObject(turtle->GetObjectIterator());
    turtle = new Engine::Image("loading/" + std::to_string((int)(tick*30+1)) + ".jpg", halfW - 504, halfH - 200, 1008, 567, 0, 0);
    AddNewObject(turtle);
    if (tick >= 4) {
        tick = 0;
        Engine::GameEngine::GetInstance().ChangeScene("lobby");
    }
}
void LoadScene::Draw() const {
    IScene::Draw();
}
void LoadScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}