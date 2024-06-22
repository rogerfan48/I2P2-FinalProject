#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Giant: public Card {
public:
    Giant(bool selected, float x, float y);
    Giant(float x, float y);
    void Draw() const override;
    void placeArmy(float xB, float yB) override;
};