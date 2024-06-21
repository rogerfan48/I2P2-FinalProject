#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class Skeletons: public Card {
public:
    Skeletons(bool selected, float x, float y);
    Skeletons(float x, float y);
    void Draw() const override;
    Army* placeArmy(int instanceID, float xB, float yB) override;
};