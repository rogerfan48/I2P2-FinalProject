#ifndef LOBBYSCENE_HPP
#define LOBBYSCENE_HPP

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include "Engine/Group.hpp"
#include "Helper/NetworkManager.hpp"

class LobbyScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    bool reloadBgm = true;
public:
    bool startWaitPairing;
    bool pairSuccessfully;

    Group* pairLabelGroup;

    LobbyScene(boost::asio::io_context& io_context);
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void CardSetOnClick(int stage);
    void SinglePlayOnClick(int stage);
    void OnlinePlayOnClick(int stage);
    void ScoreboardOnClick(int stage);
    void SettingsOnClick(int stage);
	void OnKeyDown(int keyCode) override;

    NetworkManager networkManager;
};
#endif
