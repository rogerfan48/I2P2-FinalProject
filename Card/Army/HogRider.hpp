#include "Card/Card.hpp"

#include "Entity/Army/Army.hpp"

class HogRider: public Card {
public:
    HogRider(bool selected, float x, float y);
    HogRider(float x, float y);
    void Draw() const override;
    Army* placeArmy(int instanceID, float xB, float yB) override;
};