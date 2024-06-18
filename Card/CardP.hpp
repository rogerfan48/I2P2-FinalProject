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

enum CARD_TYPE {
    ARMY, SPELL
};
// temp:
// speed: very slow:0, slow:1, median:2, fast:3, very fast:4

class Card: public Engine::IObject, public Engine::IControl {
protected:

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

    int ID;
    bool hovered;
    bool selected;

    std::string Name;
    std::shared_ptr<ALLEGRO_BITMAP> bg;
    std::shared_ptr<ALLEGRO_BITMAP> head;
    std::shared_ptr<ALLEGRO_FONT> fontName;
    std::shared_ptr<ALLEGRO_FONT> fontDesc;
    std::shared_ptr<ALLEGRO_FONT> fontDescH;
    const ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);

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
    Card(bool selected, int id, float x, float y, std::string Name,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost);

    // Spell:
    int pt;    // atk or heal
    int atkTower;
    float radius;
    float duration;
    float interval;
    Card(bool selected, int id, float x, float y, std::string Name, int pt, float radius, float duration, float interval, int atkTower=0);

    void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
};

#endif // CARD_HPP