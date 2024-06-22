#include "Giant.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Giant::Giant(bool selected, float x, float y): 
    Card(selected, 4, x, y, "Giant", "Slow but durable, only attacks buildings.", 4091, 254, 1.5, 2, 1.2, 50, 1, 5) {}
Giant::Giant(float x, float y): 
    Card(4, x, y, "Giant", 4091, 254, 1.5, 1, 1.2, 6, 1, 5) {}

void Giant::Draw() const {
    Card::Draw();
}

void Giant::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.8)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}