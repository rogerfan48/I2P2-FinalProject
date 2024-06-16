#include "Zap.hpp"

Zap::Zap(bool selected, float x, float y): 
    Card(selected, x, y, "Zap", "Zaps enemies and briefly stunning them.", 192, 2.5, 0.5) {}

void Zap::Draw() const {
    Card::Draw();
}