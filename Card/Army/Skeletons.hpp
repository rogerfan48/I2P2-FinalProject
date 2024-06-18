#include "Card/Card.hpp"

class Skeletons: public Card {
public:
    Skeletons(bool selected, float x, float y);
    Skeletons(float x, float y);
    void Draw() const override;
};