#include "Musketeer.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Musketeer::Musketeer(bool selected, float x, float y): 
    Card(selected, 2, x, y, "Musketeer", "The Musketeer is a mean shot with her trusty boomstick.", 720, 218, 1, 3, 6, 5, 1, 4) {}
Musketeer::Musketeer(float x, float y): 
    Card(2, x, y, "Musketeer", 720, 218, 1, 2, 6, 5, 1, 4) {}

void Musketeer::Draw() const {
    Card::Draw();
}

void Musketeer::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->commandToServer.push(std::to_string(ID)+" "+std::to_string(31-xB)+" "+std::to_string(yB)+" "+std::to_string(PS->gameTime-0.5));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 1, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}