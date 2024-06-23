#include "HogRider.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

HogRider::HogRider(bool selected, float x, float y): 
    Card(selected, 7, x, y, "Hog Rider", "Fast melee troop that targets buildings and can jump over the river.", 1696, 318, 1.6, 5, 1.2, 50, 1, 4) {}
HogRider::HogRider(float x, float y): 
    Card(7, x, y, "Hog Rider", 1696, 318, 1.6, 4, 1.2, 50, 1, 4) {}

void HogRider::Draw() const {
    Card::Draw();
}

void HogRider::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->commandToServer.push(std::to_string(ID)+" "+std::to_string(31-xB)+" "+std::to_string(yB)+" "+std::to_string(PS->gameTime-0.5));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}