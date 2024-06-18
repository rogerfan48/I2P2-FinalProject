#include "Card/Card.hpp"

class Wizard: public Card {
public:
    Wizard(bool selected, float x, float y);
    Wizard(float x, float y);
    void Draw() const override;
};