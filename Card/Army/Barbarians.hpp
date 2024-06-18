#include "Card/Card.hpp"

class Barbarians: public Card {
public:
    Barbarians(bool selected, float x, float y);
    Barbarians(float x, float y);
    void Draw() const override;
};