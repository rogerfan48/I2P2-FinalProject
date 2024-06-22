#include "Knight.hpp"

#include "Entity/Army/Army.hpp"

Knight::Knight(bool selected, float x, float y): 
    Card(selected, 0, x, y, "Knight", "A tough melee fighter.", 1766, 202, 1.2, 3, 1.2, 5, 1, 3) {}
Knight::Knight(float x, float y): 
    Card(0, x, y, "Knight", 1766, 202, 1.2, 2, 1.2, 5, 1, 3) {}

void Knight::Draw() const {
    Card::Draw();
}

Army* Knight::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}