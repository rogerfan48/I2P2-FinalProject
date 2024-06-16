#include "Barbarians.hpp"

Barbarians::Barbarians(bool selected, float x, float y): 
    Card(selected, 8, x, y, "Barbarians", "Spawns a pair of leveled up Barbarians.", 1341, 384, 1.4, 3, 1.2, 5, 2, 6) {}

void Barbarians::Draw() const {
    Card::Draw();
}