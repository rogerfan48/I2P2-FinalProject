#include "Wizard.hpp"

Wizard::Wizard(bool selected, float x, float y): 
    Card(selected, x, y, "Wizard", "A tough melee fighter.", 720, 281, 1.4, 2, 5.5, 5, 1, 5) {}

void Wizard::Draw() const {
    Card::Draw();
}