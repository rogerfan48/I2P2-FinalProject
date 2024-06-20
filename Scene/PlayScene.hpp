#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <string>
#include <vector>
#include <map>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/Rectangle.hpp"
#include "UI/Component/Label.hpp"
#include "Card/Card.hpp"

class PlayScene final : public Engine::IScene {
private:
    enum TILE_TYPE {
        GRASS1, // 0
        GRASS2, // 1
        BRIDGE, // 2
        ROAD,   // 3
        RIVER,  // 4
        TOWER,  // 5
        ROCK,   // 6
        CARD,   // 7
    };
    static std::map<int, ALLEGRO_COLOR> TileColor;
    static std::vector<std::string> MapTile;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    GameData& gameData = Engine::GameEngine::GetInstance().data;
    float tick;
public:
    static const int BlockSize;
    static const int MapBlockWidth;
    static const int MapBlockHeight;
    static const int CardSetHeight;
    static const int MapDiff;

    Group* TileMapGroup;
    Group* TowerGroup;
    Group* CardGroup;
    Group* ElixirGroup;
        static const int ElixirProcessWidth;
        Engine::Rectangle* elixirProcess;
        std::vector<Engine::Label*> elixirNumber;

    explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;

    void initMapTileAndTileColor();
    Card* getCardById(int id, float x, float y);
};

#endif // PLAYSCENE_HPP