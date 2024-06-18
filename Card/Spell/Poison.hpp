#include "Card/Card.hpp"

class Poison: public Card {
public:
    Poison(bool selected, float x, float y);
    void Draw() const override;
};