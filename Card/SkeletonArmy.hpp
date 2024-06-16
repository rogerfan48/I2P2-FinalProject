#include "Card.hpp"

class SkeletonArmy: public Card {
public:
    SkeletonArmy(bool selected, float x, float y);
    void Draw() const override;
};