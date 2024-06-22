#include "Archers.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Archers::Archers(bool selected, float x, float y): 
    Card(selected, 1, x, y, "Archers", "A pair of lightly armored ranged attackers.", 304, 107, 0.9, 3, 5, 5, 2, 3) {}
Archers::Archers(float x, float y): 
    Card(1, x, y, "Archers", 304, 107, 0.9, 2, 5, 5, 2, 3) {}

void Archers::Draw() const {
    Card::Draw();
}

void Archers::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 1, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.6)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 1, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.6)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}