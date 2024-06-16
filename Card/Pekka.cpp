#include "Pekka.hpp"

Pekka::Pekka(bool selected, float x, float y): 
    Card(selected, x, y, "Pekka", "A tough melee fighter.", 3760, 816, 1.8, 1, 1.2, 5, 1, 7) {}

void Pekka::Draw() const {
    Card::Draw();
}