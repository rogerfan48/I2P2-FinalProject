#include "Giant.hpp"

Giant::Giant(bool selected, float x, float y): 
    Card(selected, 4, x, y, "Giant", "Slow but durable, only attacks buildings.", 4091, 254, 1.5, 1, 1.2, 5, 1, 5) {}
Giant::Giant(float x, float y): 
    Card(4, x, y, "Giant", 4091, 254, 1.5, 1, 1.2, 5, 1, 5) {}

void Giant::Draw() const {
    Card::Draw();
}