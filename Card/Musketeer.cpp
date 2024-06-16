#include "Musketeer.hpp"

Musketeer::Musketeer(bool selected, float x, float y): 
    Card(selected, 2, x, y, "Musketeer", "The Musketeer is a mean shot with her trusty boomstick.", 720, 218, 1, 2, 6, 5, 1, 4) {}

void Musketeer::Draw() const {
    Card::Draw();
}