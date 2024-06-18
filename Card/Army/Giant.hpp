#include "Card/Card.hpp"

class Giant: public Card {
public:
    Giant(bool selected, float x, float y);
    void Draw() const override;
};