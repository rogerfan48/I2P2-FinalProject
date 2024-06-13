// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/SettingsScene.hpp"
#include "Scene/ScoreboardScene.hpp"

NewRecord newRecord;

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

	game.AddNewScene("start", new StartScene());
	game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("scoreboard", new ScoreboardScene());

    // game.Start("start", 60, 2160, 1680);	// ? ((15+2+15 + 4)*60, (18+6 + 4)*60)
	game.Start("start", 60, 1800, 1400);		// ? ((15+2+15 + 4)*50, (18+6 + 4)*50)
	// game.Start("start", 60, 1440, 1120);	// ? ((15+2+15 + 4)*40, (18+6 + 4)*40)
}