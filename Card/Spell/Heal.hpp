#include "Card/Card.hpp"

class Heal: public Card {
public:
    Heal(bool selected, float x, float y);
    Heal(float x, float y);
    void Draw() const override;
};