#include "Card/Card.hpp"

#include "Entity/Spell/Spell.hpp"

class Heal: public Card {
public:
    Heal(bool selected, float x, float y);
    Heal(float x, float y);
    void Draw() const override;

    Spell* placeSpell(int instanceID, float xB, float yB) override;
};