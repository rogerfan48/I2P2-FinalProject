#ifndef CARD_HPP
#define CARD_HPP

#include <allegro5/color.h>
#include <string>
#include <vector>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Engine/Resources.hpp"
#include "Engine/IScene.hpp"
#include "Scene/CardSetScene.hpp"
#include "Entity/Army/Army.hpp"
#include "Entity/Spell/Spell.hpp"

enum CARD_TYPE {
    ARMY, SPELL
};
// temp:
// speed: very slow:1, slow:2, median:3, fast:4, very fast:5

class Card: public Engine::IObject, public Engine::IControl {
protected:
    GameData& gameData = Engine::GameEngine::GetInstance().data;
public:
    const std::vector<std::string> IdToCard = {
        "Knight",			// 0
        "Archers",			// 1
        "Musketeer",		// 2
        "Skeletons",	// 3
        "Giant",			// 4
        "P.E.K.K.A.",		// 5
        "Wizard",			// 6
        "Hog Rider",		// 7
        "Barbarians",	// 8
        "Zap",				// 9
        "Poison",			// 10
        "Heal"				// 11
    };

    static const int CardWidth;
    static const int CardHeight;
    static const int HeadDiameter;
    static const int diff;
    static const int CardWidthP;
    static const int CardHeightP;
    static const int HeadDiameterP;
    static const int ElixirWidth;

    int ID;
    bool hovered;
    bool selected;
    bool inPlay;

    std::string Name;
    std::string Description;
    std::shared_ptr<ALLEGRO_BITMAP> bg;
    std::shared_ptr<ALLEGRO_BITMAP> head;
    std::shared_ptr<ALLEGRO_BITMAP> elixir;
    std::shared_ptr<ALLEGRO_FONT> fontName;
    std::shared_ptr<ALLEGRO_FONT> fontDesc;
    std::shared_ptr<ALLEGRO_FONT> fontDescH;
    std::shared_ptr<ALLEGRO_FONT> fontBelow;
    std::shared_ptr<ALLEGRO_FONT> fontElixirOuter;
    std::shared_ptr<ALLEGRO_FONT> fontElixir;
    const ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);
    const ALLEGRO_COLOR Black = al_map_rgb(0, 0, 0);

    CARD_TYPE cardType;
    // Army:
    int hp;
    int atk;
    float coolDown;
    float speed;
    float atkRadius;
    float detectRadius;
    int count;
    int cost;
    Card(bool selected, int id, float x, float y, std::string Name, std::string Description,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost);
    Card(int id, float x, float y, std::string Name,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost);

    // Spell:
    int pt;    // atk or heal
    int atkTower;
    float radius;
    float duration;
    float interval;
    Card(bool selected, int id, float x, float y, std::string Name, std::string Description, int pt, float radius, float duration, float interval, int atkTower, int cost);
    Card(int id, float x, float y, std::string Name, int pt, float radius, float duration, float interval, int atkTower, int cost);

    virtual Army* placeArmy(int instanceID, float xB, float yB);
    virtual Spell* placeSpell(int instanceID, float xB, float yB);

    void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
};

#endif // CARD_HPP