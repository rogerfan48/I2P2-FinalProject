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
        picRadiusPx(picRadiusBk*PlayScene::BlockSize), stunned(0), countDown(0), target(nullptr), faction(faction), isTower(isTower), 
        needForcedMove(false), previousMoveAngle(0) {
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
            side = whichSide(Position);
        }

void Army::Draw() const {
    al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
        Position.x-picRadiusPx, Position.y-picRadiusPx, 2*picRadiusPx, 2*picRadiusPx, 0);
    al_draw_circle(Position.x, Position.y, picRadiusPx, al_map_rgb(30, 30, 30), 10);
    al_draw_arc(Position.x, Position.y, picRadiusPx, -ALLEGRO_PI/2, (hp/hpMax)*ALLEGRO_PI*2, (faction?redBlood:blueBlood), 6);
    al_draw_arc(Position.x, Position.y, picRadiusPx-5, -ALLEGRO_PI/2, (countDown)?(1-countDown/coolDown)*ALLEGRO_PI*2:ALLEGRO_PI*2, (faction?redCdColor:blueCdColor), 4);
}
void Army::Update(float deltaTime) {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    if (PS->gameTime > 181) return;
    // test
    if(faction) return;
    // test
    countDown = std::max(countDown-deltaTime, 0.f);

    if (isTower && !dynamic_cast<Tower*>(this)->enabled) return;

    if (needForcedMove) {
        Position.x += std::cos(forceMoveAngle) * collisionAdjustmentLength * deltaTime;
        Position.y -= std::sin(forceMoveAngle) * collisionAdjustmentLength * deltaTime;
    }

    if (target) {
        if ((!(target->isTower) && (target->Position-Position).Magnitude() <= atkRadius) ||
            (target->isTower && (target->Position-Position).Magnitude() <= atkRadius + target->picRadiusPx - towerDetectRadiusRevision)) {
            if (countDown <= 0) {    // fire
                countDown = coolDown;
                if (Name == "Archers" || ID==-2) PS->launchBullet(new Bullet("bullet/arrow.png", 800, atk, Position.x, Position.y, 30, 15, target));
                else if (Name == "Musketeer" || ID==-1) PS->launchBullet(new Bullet("bullet/bullet.png", 1000, atk, Position.x, Position.y, 20, 20, target));
                else if (Name == "Wizard") PS->launchBullet(new Bullet("bullet/fire.png", 600, atk, Position.x, Position.y, 20, 20, target, true));
                else target->Damaged(atk);
            } else {
                // just stay
            }
        } else {
            if (ID != 4) target->beTargeted.erase(this);
            towardWhere(deltaTime);
        }
    } else {
        towardWhere(deltaTime);
    }
    needForcedMove = false;
}

void Army::Healed(float pt) {
    hp = std::min(hp + pt, hpMax);
}

void Army::Damaged(float pt) {
    hp -= pt;
    if (isTower && !dynamic_cast<Tower*>(this)->enabled) dynamic_cast<Tower*>(this)->enabled = true;
    if (hp < 1) {
        PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        if (faction) {
            for (auto i : beTargeted) i->target = nullptr;
            for (auto i : PS->WeaponGroup->GetObjects()) {
                Bullet* j = dynamic_cast<Bullet*>(i);
                if (j->target == this) PS->WeaponToBeDelete.insert(j);
            }
            if (!isTower) PS->B_ArmyGroup->RemoveObject(objectIterator);
            else PS->B_TowerGroup->RemoveObject(objectIterator);
            PS->B_ArmyGroup->AddNewObject(new Army(1,1,13,6,"Archers",1,500,1,1,1,1,1,0.7,1));
        } else PS->A_ToBeDead.insert(ID);
    }
}

void Army::towardWhere(float deltaTime) {
    target = searchTarget();
    if (needForcedMove) return;
    if (target) {   // towardArmy
        if ((side == target->side || ID==7)) {
            previousMoveAngle = findAngle(Position, target->Position);
            Position.x += std::cos(previousMoveAngle) * speed * deltaTime;
            Position.y -= std::sin(previousMoveAngle) * speed * deltaTime;
        } else if (side < target->side) {
            go(deltaTime);
        } else {
            go(deltaTime, true);
        }
    } else {
        go(deltaTime);
    }

    if (!isTower) {
        PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        for (auto i : PS->A_ArmyGroup->GetObjects()) {
            checkCollision(deltaTime, dynamic_cast<Army*>(i));
        }
        for (auto i : PS->B_ArmyGroup->GetObjects()) {
            checkCollision(deltaTime, dynamic_cast<Army*>(i));
        }
        for (auto i : PS->A_TowerGroup->GetObjects()) {
            checkCollision(deltaTime, dynamic_cast<Army*>(i));
        }
        for (auto i : PS->B_TowerGroup->GetObjects()) {
            checkCollision(deltaTime, dynamic_cast<Army*>(i));
        }
    }

    side = whichSide(Position);
}

void Army::go(float deltaTime, bool mirror) {
    Engine::Point blockPosition = pxToBlock(Position);
    if (mirror) {       // 鏡射
        switch (map[(int)blockPosition.y][(int)blockPosition.x]) {
            case U:  Position.y -= speed * deltaTime; previousMoveAngle = ALLEGRO_PI/2; break;
            case D:  Position.y += speed * deltaTime; previousMoveAngle = ALLEGRO_PI*3/2; break;
            case L:  Position.x += speed * deltaTime; previousMoveAngle = ALLEGRO_PI; break;
            case R:  Position.x -= speed * deltaTime; previousMoveAngle = 0; break;
            case UL: Position.x += std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y -= std::sin(ALLEGRO_PI/4) * speed * deltaTime; 
                previousMoveAngle = ALLEGRO_PI*3/4; break;
            case UR: Position.x -= std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y -= std::sin(ALLEGRO_PI/4) * speed * deltaTime; 
                previousMoveAngle = ALLEGRO_PI/4;break;
            case DL: Position.x += std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y += std::sin(ALLEGRO_PI/4) * speed * deltaTime; 
                previousMoveAngle = ALLEGRO_PI*5/4; break;
            case DR: Position.x -= std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y += std::sin(ALLEGRO_PI/4) * speed * deltaTime; 
                previousMoveAngle = ALLEGRO_PI*7/4; break;
            default: ;
        }
    } else {
        switch (map[(int)blockPosition.y][(int)blockPosition.x]) {
            case U:  Position.y -= speed * deltaTime; break;
            case D:  Position.y += speed * deltaTime; break;
            case L:  Position.x -= speed * deltaTime; break;
            case R:  Position.x += speed * deltaTime; break;
            case UL: Position.x -= std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y -= std::sin(ALLEGRO_PI/4) * speed * deltaTime; break;
            case UR: Position.x += std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y -= std::sin(ALLEGRO_PI/4) * speed * deltaTime; break;
            case DL: Position.x -= std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y += std::sin(ALLEGRO_PI/4) * speed * deltaTime; break;
            case DR: Position.x += std::cos(ALLEGRO_PI/4) * speed * deltaTime, Position.y += std::sin(ALLEGRO_PI/4) * speed * deltaTime; break;
            default: ;
        }
    }
}

Army* Army::searchTarget() {
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    float shortestDistance = 10000;
    float dist;
    Army* tmpTarget;
    if (ID!=4 && ID!=7)
        for (auto i : PS->B_ArmyGroup->GetObjects()) {
            Army* j = dynamic_cast<Army*>(i);
            dist = (j->Position-Position).Magnitude();
            if (dist < shortestDistance) {
                shortestDistance = dist;
                tmpTarget = j;
            }
        }
    for (auto i : PS->B_TowerGroup->GetObjects()) {
        Army* j = dynamic_cast<Army*>(i);
        dist = (j->Position-Position).Magnitude()-j->picRadiusPx - towerDetectRadiusRevision;
        if (dist < shortestDistance) {
            shortestDistance = dist;
            tmpTarget = j;
        }
    }
    if (shortestDistance < detectRadius || ID==4) {
        tmpTarget->beTargeted.insert(this);
        return tmpTarget;
    }
    else return nullptr;
}

void Army::setForceMove(float forceMoveAngle) {
    needForcedMove = false;
    this->forceMoveAngle = forceMoveAngle;
}

void Army::checkCollision(float deltaTime, Army* entity) {
    if (entity == this) return;
    if ((Position-entity->Position).Magnitude()-picRadiusPx/2-((entity->isTower)?entity->picRadiusPx:entity->picRadiusPx/2) < 0) {
        float angle = findAngle(Position, entity->Position);
        float dif = previousMoveAngle - angle;
        angle += ((dif >= 0) ? -collisionAdjustmentAngle : collisionAdjustmentAngle);
        Position.x -= std::cos(angle) * collisionAdjustmentLength * deltaTime;
        Position.y += std::sin(angle) * collisionAdjustmentLength * deltaTime;
        if (!(entity->isTower)) entity->setForceMove(angle);
    }
}