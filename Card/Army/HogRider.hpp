#include "Card/Card.hpp"

class HogRider: public Card {
public:
    HogRider(bool selected, float x, float y);
    HogRider(float x, float y);
    void Draw() const override;
};