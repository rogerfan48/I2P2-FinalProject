#include "Card/Card.hpp"

#include "Entity/Spell/Spell.hpp"

class Poison: public Card {
public:
    Poison(bool selected, float x, float y);
    Poison(float x, float y);
    void Draw() const override;

    Spell* placeSpell(int instanceID, float xB, float yB) override;
};