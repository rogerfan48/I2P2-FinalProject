#include "Archers.hpp"

Archers::Archers(bool selected, float x, float y): 
    Card(selected, 1, x, y, "Archers", "A pair of lightly armored ranged attackers.", 304, 107, 0.9, 2, 5, 5, 2, 3) {}
Archers::Archers(float x, float y): 
    Card(1, x, y, "Archers", 304, 107, 0.9, 2, 5, 5, 2, 3) {}

void Archers::Draw() const {
    Card::Draw();
}