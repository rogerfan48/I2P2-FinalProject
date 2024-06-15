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
    bool hovered;
    bool selected;

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
    Card(std::string Name, std::string Description,
        int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost) :
        cardType(ARMY), hp(hp), atk(atk), coolDown(coolDown), speed(speed), 
        atkRadius(atkRadius), detectRadius(detectRadius), count(count), cost(cost),
        Name(Name), Description(Description), hovered(false), selected(false) {}

    // Spell:
    int atk;    // or heal
    float radius;
    float time;
    Card(std::string Name, std::string Description, int atk, float radius, float time): 
        cardType(SPELL), atk(atk), radius(radius), time(time),
        Name(Name), Description(Description), hovered(false), selected(false) {}

    void Draw() const {
        if (Engine::GameEngine::GetInstance().GetActiveScene() == Engine::GameEngine::GetInstance().GetScene("cardSet")) {
            
        } else  {

        }
    }
};

#endif // CARD_HPP