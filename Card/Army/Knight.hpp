#include "Card/Card.hpp"

class Knight: public Card {
public:
    Knight(bool selected, float x, float y);
    void Draw() const override;
};