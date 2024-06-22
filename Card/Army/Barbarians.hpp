#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Barbarians: public Card {
public:
    Barbarians(bool selected, float x, float y);
    Barbarians(float x, float y);
    void Draw() const override;
    void placeArmy(float xB, float yB) override;
};