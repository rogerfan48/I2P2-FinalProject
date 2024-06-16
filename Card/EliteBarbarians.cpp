#include "EliteBarbarians.hpp"

EliteBarbarians::EliteBarbarians(bool selected, float x, float y): 
    Card(selected, x, y, "EliteBarbarians", "A tough melee fighter.", 1341, 384, 1.4, 3, 1.2, 5, 2, 6) {}

void EliteBarbarians::Draw() const {
    Card::Draw();
}