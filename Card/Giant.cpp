#include "Giant.hpp"

Giant::Giant(bool selected, float x, float y): 
    Card(selected, x, y, "Giant", "A tough melee fighter.", 4091, 254, 1.5, 1, 1.2, 5, 1, 5) {}

void Giant::Draw() const {
    Card::Draw();
}