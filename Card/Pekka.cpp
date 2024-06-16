#include "Pekka.hpp"

Pekka::Pekka(bool selected, float x, float y): 
    Card(selected, 5, x, y, "P.E.K.K.A.", "A heavily armored, slow melee fighter.", 3760, 816, 1.8, 1, 1.2, 5, 1, 7) {}

void Pekka::Draw() const {
    Card::Draw();
}