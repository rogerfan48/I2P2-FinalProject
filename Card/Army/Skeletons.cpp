#include "Skeletons.hpp"

#include "Entity/Army/Army.hpp"

Skeletons::Skeletons(bool selected, float x, float y): 
    Card(selected, 3, x, y, "Skeletons", "Spawns an army of Skeletons.", 81, 81, 1, 4, 1.2, 5, 15, 3) {}
Skeletons::Skeletons(float x, float y): 
    Card(3, x, y, "Skeletons", 81, 81, 1, 3, 1.2, 5, 15, 3) {}

void Skeletons::Draw() const {
    Card::Draw();
}

Army* Skeletons::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}