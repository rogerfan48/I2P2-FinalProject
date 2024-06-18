#include "Card/Card.hpp"

class Musketeer: public Card {
public:
    Musketeer(bool selected, float x, float y);
    void Draw() const override;
};