#include "Wizard.hpp"

Wizard::Wizard(bool selected, float x, float y): 
    Card(selected, 6, x, y, "Wizard", "Using his fireballs to cause area-damage.", 720, 281, 1.4, 2, 5.5, 5, 1, 5) {}
Wizard::Wizard(float x, float y): 
    Card(6, x, y, "Wizard", 720, 281, 1.4, 2, 5.5, 5, 1, 5) {}

void Wizard::Draw() const {
    Card::Draw();
}