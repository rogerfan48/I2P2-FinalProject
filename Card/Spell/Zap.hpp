#include "Card/Card.hpp"

#include "Entity/Spell/Spell.hpp"

class Zap: public Card {
public:
    Zap(bool selected, float x, float y);
    Zap(float x, float y);
    void Draw() const override;
    
    Spell* placeSpell(int instanceID, float xB, float yB) override;
};