#ifndef LOADSCENE_HPP
#define LOADSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LoadScene final : public Engine::IScene {
public:
    explicit LoadScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void SettingsOnClick(int stage);
    void ScoreboardOnClick(int stage);
};
#endif // LOADSCENE_HPP
