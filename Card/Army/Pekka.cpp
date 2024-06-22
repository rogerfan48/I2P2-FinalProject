#include "Pekka.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Pekka::Pekka(bool selected, float x, float y): 
    Card(selected, 5, x, y, "P.E.K.K.A.", "A heavily armored, slow melee fighter.", 3760, 816, 1.8, 2, 1.2, 5, 1, 7) {}
Pekka::Pekka(float x, float y): 
    Card(5, x, y, "P.E.K.K.A.", 3760, 816, 1.8, 1, 1.2, 5, 1, 7) {}

void Pekka::Draw() const {
    Card::Draw();
}

void Pekka::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}