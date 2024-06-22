#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Archers: public Card {
public:
    Archers(bool selected, float x, float y);
    Archers(float x, float y);
    void Draw() const override;
    void placeArmy(float xB, float yB) override;
};