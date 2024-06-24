#include "Spell.hpp"
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>

#include "Engine/Point.hpp"
#include "Helper/Helper.hpp"
#include "Scene/PlayScene.hpp"
#include "Entity/Army/Army.hpp"

Spell::Spell(int id, int instanceID, float xB, float yB, std::string Name, 
        int pt, float radius, float duration, float interval, int atkTower, ALLEGRO_COLOR color, bool faction): 
        IObject(xB, yB), ID(id), instanceID(instanceID), Name(Name), 
        pt(pt), radius(radius*PlayScene::BlockSize), time(duration), duration(duration), span(0), interval(interval), atkTower(atkTower), color(color), ready(true), readyFlash(0.15), faction(faction) {
            Position = blockToPx(Engine::Point(xB, yB));
            Position.x += PlayScene::BlockSize/2;
            Position.y += PlayScene::BlockSize/2;
        }

void Spell::Draw() const {
    if (readyFlash <= 0) {
        al_draw_filled_circle(Position.x, Position.y, radius, al_map_rgba(int(color.r*255), int(color.g*255), int(color.b*255), 40));
        al_draw_circle(Position.x, Position.y, radius-3, al_map_rgba(int(color.r*255), int(color.g*255), int(color.b*255), 120), 6);
    } else {
        al_draw_filled_circle(Position.x, Position.y, radius, al_map_rgba(int(color.r*255), int(color.g*255), int(color.b*255), 80));
        al_draw_circle(Position.x, Position.y, radius-3, al_map_rgba(int(color.r*255), int(color.g*255), int(color.b*255), 200), 6);
    }
}

void Spell::Update(float deltaTime) {
    time -= deltaTime;
    span += deltaTime;
    readyFlash -= deltaTime;
    if (ready) {
        PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        if (!faction) {
            if (Name == "Heal") {
                for (auto i : PS->A_ArmyGroup->GetObjects()) {
                    Army* j = dynamic_cast<Army*>(i);
                    if ((this->Position - j->Position).Magnitude() < this->radius) {
                        j->Healed(pt);
                    }
                }
            } else {
                for (auto i : PS->B_ArmyGroup->GetObjects()) {
                    Army* j = dynamic_cast<Army*>(i);
                    if ((this->Position - j->Position).Magnitude() < this->radius) {
                        j->Damaged(pt);
                    }
                }
                for (auto i : PS->B_TowerGroup->GetObjects()) {
                    Army* j = dynamic_cast<Army*>(i);
                    if ((this->Position - j->Position).Magnitude() < this->radius + j->picRadiusPx - Army::towerDetectRadiusRevision) {
                        j->Damaged(atkTower);
                    }
                }
            }
        } else {
            if (Name == "Heal") {
                for (auto i : PS->B_ArmyGroup->GetObjects()) {
                    Army* j = dynamic_cast<Army*>(i);
                    if ((this->Position - j->Position).Magnitude() < this->radius) {
                        j->Healed(pt);
                    }
                }
            } else {
                for (auto i : PS->A_ArmyGroup->GetObjects()) {
                    Army* j = dynamic_cast<Army*>(i);
                    if ((this->Position - j->Position).Magnitude() < this->radius) {
                        j->Damaged(pt);
                    }
                }
                for (auto i : PS->A_TowerGroup->GetObjects()) {
                    Army* j = dynamic_cast<Army*>(i);
                    if ((this->Position - j->Position).Magnitude() < this->radius + j->picRadiusPx - Army::towerDetectRadiusRevision) {
                        j->Damaged(atkTower);
                    }
                }
            }
        }
        ready = false;
    }
    if (span > interval) {
        ready = true;
        readyFlash = 0.15;
        span = 0;
    }
}