#include "Knight.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Knight::Knight(bool selected, float x, float y): 
    Card(selected, 0, x, y, "Knight", "A tough melee fighter.", 1766, 202, 1.2, 3, 1.2, 5, 1, 3) {}
Knight::Knight(float x, float y): 
    Card(0, x, y, "Knight", 1766, 202, 1.2, 2, 1.2, 5, 1, 3) {}

void Knight::Draw() const {
    Card::Draw();
}

void Knight::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->commandToServer.push(std::to_string(ID)+" "+std::to_string(int(31-xB))+" "+std::to_string(int(yB))+" "+std::to_string(PS->gameTime-0.5)+"\n");

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 0, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}