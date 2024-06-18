#include "Card/Card.hpp"

class Zap: public Card {
public:
    Zap(bool selected, float x, float y);
    Zap(float x, float y);
    void Draw() const override;
};