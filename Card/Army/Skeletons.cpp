#include "Skeletons.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Skeletons::Skeletons(bool selected, float x, float y): 
    Card(selected, 3, x, y, "Skeletons", "Spawns an army of Skeletons.", 81, 81, 1, 4, 1.2, 5, 15, 3) {}
Skeletons::Skeletons(float x, float y): 
    Card(3, x, y, "Skeletons", 81, 81, 1, 3, 1.2, 5, 15, 3) {}

void Skeletons::Draw() const {
    Card::Draw();
}

void Skeletons::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->commandToServer.push(std::to_string(ID)+" "+std::to_string(int(31-xB))+" "+std::to_string(int(yB))+" "+std::to_string(PS->gameTime-0.5)+"\n");
    
    for (int i=0; i<15; i++) {
        PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.5)});
        PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
    }
}