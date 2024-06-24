#include "Poison.hpp"

#include "Helper/Helper.hpp"
#include "Entity/Spell/Spell.hpp"
#include "Scene/PlayScene.hpp"

Poison::Poison(bool selected, float x, float y): 
    Card(selected, 10, x, y, "Poison", "Covers the area in a deadly toxin.", 78, 4, 8, 1, 23, 4) {
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 16);
        fontDescH = Engine::Resources::GetInstance().GetFont("recharge.otf", 17);
    }
Poison::Poison(float x, float y): 
    Card(10, x, y, "Poison", 78, 4, 8, 1, 23, 4) {
    }

void Poison::Draw() const {
    Card::Draw();
    if (!inPlay) {
        if (!hovered) {
            al_draw_text(fontDesc.get(), White, Position.x+200-10, Position.y+90, 0,  ("Atk: "+std::to_string(pt)).c_str());
            al_draw_text(fontDesc.get(), White, Position.x+200-10, Position.y+125, 0, ("Atk Tower: "+std::to_string(atkTower)).c_str());
            al_draw_text(fontDesc.get(), White, Position.x+200-10, Position.y+160, 0, ("Radius: "+floatToStr(radius)).c_str());
            al_draw_text(fontDesc.get(), White, Position.x+200-10, Position.y+195, 0, ("Duration: "+floatToStr(duration)).c_str());
        } else {
            Engine::Point nP(Position); nP.x-=diff; nP.y-=diff;
            al_draw_text(fontDescH.get(), White, nP.x+200-10, nP.y+90, 0,  ("Atk: "+std::to_string(pt)).c_str());
            al_draw_text(fontDescH.get(), White, nP.x+200-10, nP.y+125+2, 0, ("Atk Tower: "+std::to_string(atkTower)).c_str());
            al_draw_text(fontDescH.get(), White, nP.x+200-10, nP.y+160+4, 0, ("Radius: "+floatToStr(radius)).c_str());
            al_draw_text(fontDescH.get(), White, nP.x+200-10, nP.y+195+6, 0, ("Duration: "+floatToStr(duration)).c_str());
        }
    } else {
        if (!hovered) {
            al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+90, 0,  ("Atk: "+std::to_string(pt)).c_str());
            al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+130, 0, ("Atk T: "+std::to_string(atkTower)).c_str());
            al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+170, 0, ("Rad.: "+floatToStr(radius)).c_str());
            al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+210, 0, ("Dur.: "+floatToStr(duration)).c_str());
        } else {
            Engine::Point nP(Position); nP.x-=diff; nP.y-=diff;
            al_draw_text(fontDescH.get(), White, nP.x+220, nP.y+90, 0,  ("Atk: "+std::to_string(pt)).c_str());
            al_draw_text(fontDescH.get(), White, nP.x+220, nP.y+130+2, 0, ("Atk T: "+std::to_string(atkTower)).c_str());
            al_draw_text(fontDescH.get(), White, nP.x+220, nP.y+170+4, 0, ("Rad.: "+floatToStr(radius)).c_str());
            al_draw_text(fontDescH.get(), White, nP.x+220, nP.y+210+6, 0, ("Dur.: "+floatToStr(duration)).c_str());
        }
    }
}

Spell* Poison::placeSpell(int instanceID, float xB, float yB) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    PS->commandToServer.push(std::to_string(ID)+" "+std::to_string(int(31-xB))+" "+std::to_string(int(yB))+" "+std::to_string(PS->gameTime-0.5)+"\n");

    return new Spell(ID, instanceID, xB, yB, Name, pt, radius, duration, interval, atkTower, al_map_rgb(150, 50, 30));
}