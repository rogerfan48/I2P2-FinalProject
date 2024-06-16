#include "Card.hpp"

class EliteBarbarians: public Card {
public:
    EliteBarbarians(bool selected, float x, float y);
    void Draw() const override;
};