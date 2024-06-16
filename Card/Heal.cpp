#include "Heal.hpp"

Heal::Heal(bool selected, float x, float y): 
    Card(selected, x, y, "Heal", "Heals enemies and briefly stunning them.", 75, 3.5, 8) {}

void Heal::Draw() const {
    Card::Draw();
}