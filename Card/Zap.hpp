#include "Card.hpp"

class Zap: public Card {
public:
    Zap(bool selected, float x, float y);
    void Draw() const override;
};