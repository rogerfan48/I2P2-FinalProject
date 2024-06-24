#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "UI/Component/Circle.hpp"
#include "UI/Component/CircleBorder.hpp"
#include "UI/Component/Rectangle.hpp"
#include "UI/Component/RectangleBorder.hpp"
#include "UI/Component/Label.hpp"
#include "Card/Card.hpp"
#include "Tower/Tower.hpp"
#include "Weapon/Bullet.hpp"

class PlayScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    GameData& gameData = Engine::GameEngine::GetInstance().data;
    Engine::Point mousePos;
    bool victory = false;
public:
    bool onlineMode;
    std::queue<std::string> commandFromServer;
    std::queue<std::string> commandToServer;

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
    
    float tick;
    float gameTime;
    int instanceIDCounter;

    static const int BlockSize;
    static const int MapBlockWidth;
    static const int MapBlockHeight;
    static const int CardSetHeight;
    static const int MapDiff;

    Group* TileMapGroup;
        Engine::Rectangle* prohibitedMask;
        Engine::RectangleBorder* prohibitedMaskBorder;
    Group* CardGroup;
        Card* selectedCard;
        std::vector<Card*> cardPointer;
    // Preview:
        Engine::Rectangle* placePreview;
        Engine::RectangleBorder* placePreviewBorder;
        Engine::Label* placeReviewName;
        Engine::Circle* radiusPreview;
        Engine::CircleBorder* radiusPreviewBorder;
    Group* A_TowerGroup;
        std::map<int, Tower*> A_TowerPtrMap;
        std::set<int> A_TowerToBeRemoved;
    Group* A_ArmyGroup;
        std::map<int, Army*> A_ArmyPtrMap;
        std::set<int> A_ToBeDead;
        std::queue<std::pair<float, Army*>> A_ArmyToBeDeployed;
    Group* A_SpellGroup;
        std::queue<std::pair<float, Spell*>> A_SpellToBeDeployed;
    Group* B_TowerGroup;
        std::map<int, Tower*> B_TowerPtrMap;
        std::set<int> B_TowerToBeRemoved;
    Group* B_ArmyGroup;
        std::map<int, Army*> B_ArmyPtrMap;
        std::set<int> B_ToBeDead;
        std::queue<std::pair<float, Army*>> B_ArmyToBeDeployed;
        std::queue<std::pair<int, Engine::Point>> B_WaitForDeployed;         // for single
        std::set<int> B_CardSelect;
    Group* B_SpellGroup;
        std::queue<std::pair<float, Spell*>> B_SpellToBeDeployed;
    // Group* MapBorderGroup;
    Group* TimeDisplayGroup;
        bool isTimeShown;
        float timeShown;
    Group* ElixirGroup;
        static const int ElixirProcessWidth;
        Engine::Rectangle* elixirProcess;
        std::vector<Engine::Label*> elixirNumber;
    Group* WeaponGroup;
        std::set<Bullet*> WeaponToBeDelete;
    Group* Elixir2xGroup;

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
    bool mouseInPlay();
    bool mouseAtValid();
    void launchBullet(Bullet*);

    void showWinAnimation();
    void showLoseAnimation();

    static void writeToServer(tcp::socket& socket);
    static void readFromServer(tcp::socket& socket);

    void putOpponentEntity();
    void deployAccordingID(int ID, int xB, int yB, int t);
    int singleMode(int ID);
    int cardCost(int ID);
};

#endif // PLAYSCENE_HPP