#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/RectangleButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Slider.hpp"
#include "SettingScene.hpp"

extern std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmLobby;

void SettingScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::RectangleButton *btn;

    AddNewObject(new Engine::Label("Setting", "recharge.otf", 72, halfW, halfH/3, 255, 255, 255, 255, 0.5, 0.5));

    // Slider
    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(halfW-100, halfH-100, 300, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&SettingScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "recharge.otf", 42, halfW-180, halfH-100, 255, 255, 255, 255, 0.5, 0.5));
    sliderBGM->SetValue(AudioHelper::BGMVolume);

    sliderSFX = new Slider(halfW-100, halfH, 300, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&SettingScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "recharge.otf", 42, halfW-180, halfH, 255, 255, 255, 255, 0.5, 0.5));
    sliderSFX->SetValue(AudioHelper::SFXVolume);

    // Back
    btn = new Engine::RectangleButton(halfW-250, halfH*3/2-50, 500, 100, al_map_rgb(170, 90, 30), al_map_rgb(200, 140, 70));
    btn->SetOnClickCallback(std::bind(&SettingScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "recharge.otf", 52, halfW, halfH*3/2, 0, 0, 0, 255, 0.5, 0.5));
}
void SettingScene::Terminate() {
    IScene::Terminate();
}
void SettingScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("lobby");
}
void SettingScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if(keyCode == ALLEGRO_KEY_ESCAPE) Engine::GameEngine::GetInstance().ChangeScene("lobby");
}
void SettingScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmLobby, value);
    AudioHelper::BGMVolume = value;
}
void SettingScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
