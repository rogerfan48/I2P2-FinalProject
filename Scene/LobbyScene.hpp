#ifndef LOBBYSCENE_HPP
#define LOBBYSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LobbyScene final : public Engine::IScene {
public:
    explicit LobbyScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void SettingsOnClick(int stage);
    void ScoreboardOnClick(int stage);
};
#endif
