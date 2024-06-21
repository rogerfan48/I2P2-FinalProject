#include "Pekka.hpp"

#include "Entity/Army/Army.hpp"

Pekka::Pekka(bool selected, float x, float y): 
    Card(selected, 5, x, y, "P.E.K.K.A.", "A heavily armored, slow melee fighter.", 3760, 816, 1.8, 1, 1.2, 5, 1, 7) {}
Pekka::Pekka(float x, float y): 
    Card(5, x, y, "P.E.K.K.A.", 3760, 816, 1.8, 1, 1.2, 5, 1, 7) {}

void Pekka::Draw() const {
    Card::Draw();
}

Army* Pekka::placeArmy(int instanceID, float xB, float yB) {
    return new Army(ID, instanceID, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7);
}