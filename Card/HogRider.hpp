#include "Card.hpp"

class HogRider: public Card {
public:
    HogRider(bool selected, float x, float y);
    void Draw() const override;
};