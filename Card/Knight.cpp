#include "Knight.hpp"

Knight::Knight(bool selected, float x, float y): 
    Card(selected, x, y, "Knight", "A tough melee fighter.", 1766, 202, 1.2, 2, 1.2, 5, 1, 3) {}

void Knight::Draw() const {
    Card::Draw();
}