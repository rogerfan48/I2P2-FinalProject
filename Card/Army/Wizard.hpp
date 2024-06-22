#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Wizard: public Card {
public:
    Wizard(bool selected, float x, float y);
    Wizard(float x, float y);
    void Draw() const override;
    void placeArmy(float xB, float yB) override;
};