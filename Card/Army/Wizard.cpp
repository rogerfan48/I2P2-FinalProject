#include "Wizard.hpp"

#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Wizard::Wizard(bool selected, float x, float y): 
    Card(selected, 6, x, y, "Wizard", "Using his fireballs to cause area-damage.", 720, 281, 1.4, 3, 5.5, 5, 1, 5) {}
Wizard::Wizard(float x, float y): 
    Card(6, x, y, "Wizard", 720, 281, 1.4, 2, 5.5, 5, 1, 5) {}

void Wizard::Draw() const {
    Card::Draw();
}

void Wizard::placeArmy(float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

    PS->commandToServer.push(std::to_string(ID)+" "+std::to_string(31-xB)+" "+std::to_string(yB)+" "+std::to_string(PS->gameTime-0.5));

    PS->A_ArmyPtrMap.insert({PS->instanceIDCounter, new Army(ID, PS->instanceIDCounter, xB, yB, Name, 1, hp, atk, coolDown, speed, atkRadius, detectRadius, 0.7)});
    PS->A_ArmyToBeDeployed.push({PS->gameTime-0.5, PS->A_ArmyPtrMap[PS->instanceIDCounter++]});
}