#ifndef CARDSETSCENE_HPP
#define CARDSETSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/RectangleButton.hpp"
#include "Card/Card.hpp"

class CardSetScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    UserData& userData = Engine::GameEngine::GetInstance().userData;
    std::set<int> newCardSet;

    Group* CardGroup;
    Engine::RectangleButton* saveButton;

    explicit CardSetScene() = default;
    void Initialize() override;
    void Terminate() override;
    void SaveOnClick(int stage);
    void BackOnClick(int stage);
	void OnKeyDown(int keyCode) override;
};

#endif // CARDSETSCENE_HPP