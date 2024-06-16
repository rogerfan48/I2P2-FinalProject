#ifndef LOBBYSCENE_HPP
#define LOBBYSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LobbyScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    bool reloadBgm = true;
public:
    explicit LobbyScene() = default;
    void Initialize() override;
    void Terminate() override;
    void CardSetOnClick(int stage);
    void SinglePlayOnClick(int stage);
    void OnlinePlayOnClick(int stage);
    void ScoreboardOnClick(int stage);
    void SettingsOnClick(int stage);
	void OnKeyDown(int keyCode) override;
};
#endif
