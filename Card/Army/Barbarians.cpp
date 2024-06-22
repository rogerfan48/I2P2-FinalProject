#include "Barbarians.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Barbarians::Barbarians(bool selected, float x, float y): 
    Card(selected, 8, x, y, "Barbarians", "Spawns a pair of leveled up Barbarians.", 1341, 384, 1.4, 4, 1.2, 5, 2, 6) {}
Barbarians::Barbarians(float x, float y): 
    Card(8, x, y, "Barbarians", 1341, 384, 1.4, 3, 1.2, 5, 2, 6) {}

void Barbarians::Draw() const {
    Card::Draw();
}

void Barbarians::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}