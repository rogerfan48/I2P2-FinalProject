#include "Army.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>

#include "Engine/Point.hpp"
#include "Engine/LOG.hpp"
#include "Helper/Helper.hpp"
#include "Scene/PlayScene.hpp"
#include "Tower/Tower.hpp"

Army::Army(int id, int instanceID, float xB, float yB, std::string Name,
    bool bullet, int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk, int faction, bool isTower): 
        IObject(xB, yB), ID(id), instanceID(instanceID), Name(Name), 
        fireBullet(bullet), hp(hp), hpMax(hp), atk(atk), coolDown(coolDown), speedOri(speed), atkRadius(atkRadius*PlayScene::BlockSize), detectRadius(detectRadius*PlayScene::BlockSize),
        picRadiusPx(picRadiusBk*PlayScene::BlockSize), stunned(0), countDown(0), target(nullptr), faction(faction), isTower(isTower) {
            side = whichSide(Position);
            if (!isTower) {
                Position = blockToMiddlePx(Engine::Point(xB, yB));
                head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
            } else if (id==-1) Position = blockToPx(Engine::Point(xB, yB));
            else Position = blockToMiddlePx(Engine::Point(xB, yB));
            switch (int(speed)) {
                case (1): this->speed = 40; break;
                case (2): this->speed = 60; break;
                case (3): this->speed = 80; break;
                case (4): this->speed = 100; break;
                case (5): this->speed = 120; break;
            }
        }

void Army::Draw() const {
    al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
        Position.x-picRadiusPx, Position.y-picRadiusPx, 2*picRadiusPx, 2*picRadiusPx, 0);
    al_draw_circle(Position.x, Position.y, picRadiusPx, al_map_rgb(30, 30, 30), 10);
    al_draw_arc(Position.x, Position.y, picRadiusPx, -1.57, (hp/hpMax)*6.28, (faction?redBlood:blueBlood), 6);
}
void Army::Update(float deltaTime) {
    // test
    if(faction) return;
    // test
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    countDown -= deltaTime;

    if (target) {
        if ((!(target->isTower) && (target->Position-Position).Magnitude() <= atkRadius) ||
            (target->isTower && (target->Position-Position).Magnitude() <= atkRadius + target->picRadiusPx)) {
            if (countDown < 0) {    // fire
                countDown = coolDown;
                if (Name == "Archers") PS->launchBullet(new Bullet("bullet/arrow.png", 800, atk, Position.x, Position.y, 10, 30, target));
                else if (Name == "Musketeer") PS->launchBullet(new Bullet("bullet/bullet.png", 1000, atk, Position.x, Position.y, 20, 20, target));
                else /* Wizard */ PS->launchBullet(new Bullet("bullet/fire.png", 600, atk, Position.x, Position.y, 20, 20, target, true));
            } else {
                // just stay
            }
        } else {
            target->beTargeted.erase(this);
            towardWhere(deltaTime);
        }
    } else {
        towardWhere(deltaTime);
    }
}

void Army::Healed(float pt) {
    hp = std::min(hp + pt, hpMax);
}
void Army::Damaged(float pt) {
    hp -= pt;
    if (hp < 0) {
        PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        PS->A_ToBeDead.insert(ID);
    }
}

void Army::towardWhere(float deltaTime) {
    target = searchTarget();
    if (target) {   // towardArmy
        if (side == target->side) {
            Position.x += cos(findAngle(Position, target->Position)) * speed * deltaTime;
            Position.y += sin(findAngle(Position, target->Position)) * speed * deltaTime;
        } else if (side < target->side) {
            go(deltaTime);
        } else {
            go(deltaTime, true);
        }
    } else {
        go(deltaTime);
    }
    side = whichSide(Position);
}

void Army::go(float deltaTime, bool mirror) {
    Engine::Point blockPosition = pxToBlock(Position);
    if (mirror) {       // 鏡射
        switch (map[(int)blockPosition.y][(int)blockPosition.x]) {
            case U:  Position.y -= speed * deltaTime; break;
            case D:  Position.y += speed * deltaTime; break;
            case L:  Position.x += speed * deltaTime; break;
            case R:  Position.x -= speed * deltaTime; break;
            case UL: Position.x += cos(45) * speed * deltaTime, Position.y -= sin(45) * speed * deltaTime; break;
            case UR: Position.x -= cos(45) * speed * deltaTime, Position.y -= sin(45) * speed * deltaTime; break;
            case DL: Position.x += cos(45) * speed * deltaTime, Position.y += sin(45) * speed * deltaTime; break;
            case DR: Position.x -= cos(45) * speed * deltaTime, Position.y += sin(45) * speed * deltaTime; break;
            default: ;
        }
    } else {
        switch (map[(int)blockPosition.y][(int)blockPosition.x]) {
            case U:  Position.y -= speed * deltaTime; break;
            case D:  Position.y += speed * deltaTime; break;
            case L:  Position.x -= speed * deltaTime; break;
            case R:  Position.x += speed * deltaTime; break;
            case UL: Position.x -= cos(45) * speed * deltaTime, Position.y -= sin(45) * speed * deltaTime; break;
            case UR: Position.x += cos(45) * speed * deltaTime, Position.y -= sin(45) * speed * deltaTime; break;
            case DL: Position.x -= cos(45) * speed * deltaTime, Position.y += sin(45) * speed * deltaTime; break;
            case DR: Position.x += cos(45) * speed * deltaTime, Position.y += sin(45) * speed * deltaTime; break;
            default: ;
        }
    }
}

Army* Army::searchTarget() {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    float shortestDistance = 10000;
    float dist;
    Army* tmpTarget;
    for (auto i : PS->B_ArmyGroup->GetObjects()) {
        Army* j = dynamic_cast<Army*>(i);
        dist = (j->Position-Position).Magnitude();
        if (dist < shortestDistance) {
            shortestDistance = dist;
            tmpTarget = j;
        }
    }
    for (auto i : PS->B_TowerGroup->GetObjects()) {
        Tower* j = dynamic_cast<Tower*>(i);
        dist = (j->Position-Position).Magnitude()-j->picRadiusPx;
        if (dist < shortestDistance) {
            shortestDistance = dist;
            tmpTarget = j;
        }
    }
    if (shortestDistance < detectRadius) {
        tmpTarget->beTargeted.insert(this);
        return tmpTarget;
    }
    else return nullptr;
}