#include "Musketeer.hpp"

#include "Entity/Army/Army.hpp"

Musketeer::Musketeer(bool selected, float x, float y): 
    Card(selected, 2, x, y, "Musketeer", "The Musketeer is a mean shot with her trusty boomstick.", 720, 218, 1, 2, 6, 5, 1, 4) {}
Musketeer::Musketeer(float x, float y): 
    Card(2, x, y, "Musketeer", 720, 218, 1, 2, 6, 5, 1, 4) {}

void Musketeer::Draw() const {
    Card::Draw();
}

Army* Musketeer::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}