#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Engine/Resources.hpp"

enum CARD_TYPE {
    ARMY, SPELL
};
// temp:
// speed: very slow:0, slow:1, median:2, fast:3, very fast:4

class Card: public Engine::IObject, Engine::IControl {
protected:

public:
    static const int CardWidth;
    static const int CardHeight;
    static const int HeadDiameter;

    bool hovered;
    bool selected;

    std::string Name;
    std::string Description;
    std::shared_ptr<ALLEGRO_BITMAP> bg;
    std::shared_ptr<ALLEGRO_BITMAP> head;
    std::shared_ptr<ALLEGRO_FONT> fontName;
    std::shared_ptr<ALLEGRO_FONT> fontDesc;
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
    Card(bool selected, float x, float y, std::string Name, std::string Description,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost);

    // Spell:
    int pt;    // atk or heal
    float radius;
    float time;
    Card(bool selected, float x, float y, std::string Name, std::string Description, int pt, float radius, float time);

    void Draw() const override;
};

#endif // CARD_HPP