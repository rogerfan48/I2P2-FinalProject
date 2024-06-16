#include "Archers.hpp"

Archers::Archers(bool selected, float x, float y): 
    Card(selected, x, y, "Archers", "A tough melee fighter.", 304, 107, 0.9, 2, 5, 5, 2, 3) {}

void Archers::Draw() const {
    Card::Draw();
}