#include "Card/Card.hpp"

class Archers: public Card {
public:
    Archers(bool selected, float x, float y);
    void Draw() const override;
};