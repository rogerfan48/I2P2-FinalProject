#ifndef CARD_HPP
#define CARD_HPP

#include <string>

#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

enum CARD_TYPE {
    ARMY, SPELL
};
class Card: public Engine::IObject, Engine::IControl {
protected:

public:
    static const int CardWidth = 325;
    static const int CardHeight = 267;

    bool hovered;
    bool selected;
    bool atCardSet;

    std::string Name;
    std::string Description;

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
    Card(bool atCardSet, float x, float y, float w, float h,
        std::string Name, std::string Description,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost) :
        Engine::IObject(x, y, w, h), cardType(ARMY), hp(hp), atk(atk), coolDown(coolDown), speed(speed), 
        atkRadius(atkRadius), detectRadius(detectRadius), count(count), cost(cost),
        Name(Name), Description(Description), hovered(false), selected(false) {}

    // Spell:
    int atk;    // or heal
    float radius;
    float time;
    Card(std::string Name, int atk, float radius, float time): 
        cardType(SPELL), atk(atk), radius(radius), time(time),
        Name(Name), hovered(false), selected(false) {}

    void Draw() const {
        if (Engine::GameEngine::GetInstance().GetActiveScene() == Engine::GameEngine::GetInstance().GetScene("cardSet")) {
            
        } else  {

        }
    }
};

#endif // CARD_HPP