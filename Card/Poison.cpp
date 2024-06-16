#include "Poison.hpp"

Poison::Poison(bool selected, float x, float y): 
    Card(selected, x, y, "Poison", "Poisons enemies and briefly stunning them.", 91, 3.5, 8) {}

void Poison::Draw() const {
    Card::Draw();
}