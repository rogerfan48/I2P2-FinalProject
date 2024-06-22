#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Musketeer: public Card {
public:
    Musketeer(bool selected, float x, float y);
    Musketeer(float x, float y);
    void Draw() const override;
    void placeArmy(float xB, float yB) override;
};