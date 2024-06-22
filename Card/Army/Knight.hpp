#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Knight: public Card {
public:
    Knight(bool selected, float x, float y);
    Knight(float x, float y);
    void Draw() const override;
    void placeArmy(float xB, float yB) override;
};