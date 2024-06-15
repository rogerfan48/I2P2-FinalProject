#ifndef CARDSETSCENE_HPP
#define CARDSETSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class CardSetScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit CardSetScene() = default;
    void Initialize() override;
    void Terminate() override;
    void CheckOnClick(int stage);
    void BackOnClick(int stage);
};

#endif // CARDSETSCENE_HPP