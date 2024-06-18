#include "Scene/CardSetScene.hpp"
#include <allegro5/allegro_audio.h>
#include <string>
#include <set>

#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/RectangleButton.hpp"
#include "UI/Component/Label.hpp"

#include "Card/Army/Knight.hpp"
#include "Card/Army/Archers.hpp"
#include "Card/Army/Musketeer.hpp"
#include "Card/Army/Skeletons.hpp"
#include "Card/Army/Giant.hpp"
#include "Card/Army/Pekka.hpp"
#include "Card/Army/Wizard.hpp"
#include "Card/Army/HogRider.hpp"
#include "Card/Army/Barbarians.hpp"
#include "Card/Spell/Zap.hpp"
#include "Card/Spell/Poison.hpp"
#include "Card/Spell/Heal.hpp"

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

    AddNewControlObject(CardGroup = new Group());

    newCardSet = userData.chosenCards;
    CardGroup->AddNewControlObject(new Knight(newCardSet.find(0)!=newCardSet.end(), 140, 200));
    CardGroup->AddNewControlObject(new Archers(newCardSet.find(1)!=newCardSet.end(), 530, 200));
    CardGroup->AddNewControlObject(new Musketeer(newCardSet.find(2)!=newCardSet.end(), 920, 200));
    CardGroup->AddNewControlObject(new Skeletons(newCardSet.find(3)!=newCardSet.end(), 1310, 200));
    CardGroup->AddNewControlObject(new Giant(newCardSet.find(4)!=newCardSet.end(), 140, 490));
    CardGroup->AddNewControlObject(new Pekka(newCardSet.find(5)!=newCardSet.end(), 530, 490));
    CardGroup->AddNewControlObject(new Wizard(newCardSet.find(6)!=newCardSet.end(), 920, 490));
    CardGroup->AddNewControlObject(new HogRider(newCardSet.find(7)!=newCardSet.end(), 1310, 490));
    CardGroup->AddNewControlObject(new Barbarians(newCardSet.find(8)!=newCardSet.end(), 140, 780));
    CardGroup->AddNewControlObject(new Zap(newCardSet.find(9)!=newCardSet.end(), 530, 780));
    CardGroup->AddNewControlObject(new Poison(newCardSet.find(10)!=newCardSet.end(), 920, 780));
    CardGroup->AddNewControlObject(new Heal(newCardSet.find(11)!=newCardSet.end(), 1310, 780));

    btn = new Engine::RectangleButton(300, 1220, 500, 100, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&CardSetScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "recharge.otf", 52, 550, 1270, 0, 0, 0, 255, 0.5, 0.5));

    saveButton = btn = new Engine::RectangleButton(1000, 1220, 500, 100, btnColor, btnColorHovered);
    btn->SetOnClickCallback(std::bind(&CardSetScene::SaveOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Save", "recharge.otf", 52, 1250, 1270, 0, 0, 0, 255, 0.5, 0.5));
}
void CardSetScene::Terminate() {
    IScene::Terminate();
}
void CardSetScene::SaveOnClick(int stage) {
    if (saveButton->Enabled && userData.chosenCards != newCardSet) {
        userData.chosenCards = newCardSet;
        AudioHelper::PlaySample("buttonPressed.ogg", false, (AudioHelper::SFXVolume+0.4<=1) ? (AudioHelper::SFXVolume+0.4) : 1);
    }
}
void CardSetScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("lobby");
}
void CardSetScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if(keyCode == ALLEGRO_KEY_ESCAPE) Engine::GameEngine::GetInstance().ChangeScene("lobby");
    else if(keyCode == ALLEGRO_KEY_ENTER) SaveOnClick(2);
}