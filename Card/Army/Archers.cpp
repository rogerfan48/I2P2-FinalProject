#include "Archers.hpp"

#include "Entity/Army/Army.hpp"

Archers::Archers(bool selected, float x, float y): 
    Card(selected, 1, x, y, "Archers", "A pair of lightly armored ranged attackers.", 304, 107, 0.9, 3, 5, 5, 2, 3) {}
Archers::Archers(float x, float y): 
    Card(1, x, y, "Archers", 304, 107, 0.9, 2, 5, 5, 2, 3) {}

void Archers::Draw() const {
    Card::Draw();
}

Army* Archers::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, 1, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}