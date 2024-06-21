#include "HogRider.hpp"

#include "Entity/Army/Army.hpp"

HogRider::HogRider(bool selected, float x, float y): 
    Card(selected, 7, x, y, "Hog Rider", "Fast melee troop that targets buildings and can jump over the river.", 1696, 318, 1.6, 4, 1.2, 5, 1, 4) {}
HogRider::HogRider(float x, float y): 
    Card(7, x, y, "Hog Rider", 1696, 318, 1.6, 4, 1.2, 5, 1, 4) {}

void HogRider::Draw() const {
    Card::Draw();
}

Army* HogRider::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}