#include "Musketeer.hpp"

Musketeer::Musketeer(bool selected, float x, float y): 
    Card(selected, x, y, "Musketeer", "A tough melee fighter.", 720, 218, 1, 2, 6, 5, 1, 4) {}

void Musketeer::Draw() const {
    Card::Draw();
}