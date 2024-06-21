#include "Barbarians.hpp"

#include "Entity/Army/Army.hpp"

Barbarians::Barbarians(bool selected, float x, float y): 
    Card(selected, 8, x, y, "Barbarians", "Spawns a pair of leveled up Barbarians.", 1341, 384, 1.4, 3, 1.2, 5, 2, 6) {}
Barbarians::Barbarians(float x, float y): 
    Card(8, x, y, "Barbarians", 1341, 384, 1.4, 3, 1.2, 5, 2, 6) {}

void Barbarians::Draw() const {
    Card::Draw();
}

Army* Barbarians::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}