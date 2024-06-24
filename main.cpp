#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoadScene.hpp"
#include "Scene/LobbyScene.hpp"
#include "Scene/CardSetScene.hpp"
#include "Scene/SettingScene.hpp"
#include "Scene/PlayScene.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

	game.AddNewScene("load", new LoadScene());
	game.AddNewScene("lobby", new LobbyScene(game.io_context));
	game.AddNewScene("cardSet", new CardSetScene());
	game.AddNewScene("setting", new SettingScene());
	game.AddNewScene("play", new PlayScene());

	game.Start("load", 60, 1800, 1400);		// ? ((15+2+15 + 4) * 50, (18+6 + 4) * 50)
}