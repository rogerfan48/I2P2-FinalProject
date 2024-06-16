#include "SkeletonArmy.hpp"

SkeletonArmy::SkeletonArmy(bool selected, float x, float y): 
    Card(selected, x, y, "SkeletonArmy", "A tough melee fighter.", 81, 81, 1, 3, 1.2, 5, 15, 3) {}

void SkeletonArmy::Draw() const {
    Card::Draw();
}