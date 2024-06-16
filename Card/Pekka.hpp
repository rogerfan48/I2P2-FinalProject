#include "Card.hpp"

class Pekka: public Card {
public:
    Pekka(bool selected, float x, float y);
    void Draw() const override;
};