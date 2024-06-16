#include "HogRider.hpp"

HogRider::HogRider(bool selected, float x, float y): 
    Card(selected, x, y, "HogRider", "A tough melee fighter.", 1696, 318, 1.6, 4, 1.2, 5, 1, 4) {}

void HogRider::Draw() const {
    Card::Draw();
}