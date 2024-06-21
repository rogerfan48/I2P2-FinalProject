#include "Army.hpp"
#include <allegro5/allegro.h>
#include <algorithm>

#include "Engine/Point.hpp"
#include "Engine/LOG.hpp"
#include "Helper/Helper.hpp"
#include "Scene/PlayScene.hpp"

Army::Army(int id, int instanceID, float xB, float yB, std::string Name,
    bool bullet, int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk, int faction): 
        IObject(xB, yB), ID(id), instanceID(instanceID), Name(Name), 
        fireBullet(bullet), hp(hp), hpMax(hp), atk(atk), coolDown(coolDown), speed(speed), speedOri(speed), atkRadius(atkRadius), detectRadius(detectRadius), picRadiusPx(picRadiusBk*PlayScene::BlockSize),
        stunned(0), countDown(0), target(nullptr), faction(faction) {
            Position = blockToPx(Engine::Point(xB, yB));
            Position.x += PlayScene::BlockSize/2;
            Position.y += PlayScene::BlockSize/2;
            head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        }

void Army::Draw() const {
    al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
        Position.x-picRadiusPx, Position.y-picRadiusPx, 2*picRadiusPx, 2*picRadiusPx, 0);
}
void Army::Update(float deltaTime) {
    // test
    if(faction) return;
    // test
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    countDown -= deltaTime;
    target = searchTarget();
    if (countDown < 0) {
        if (target) {
            if ((target->Position-Position).Magnitude() <= atkRadius) {
                countDown = coolDown;
                if (Name == "Archers") PS->launchBullet(new Bullet("bullet/arrow.png", 800, atk, Position.x, Position.y, 10, 30, target));
                else if (Name == "Musketeer") PS->launchBullet(new Bullet("bullet/bullet.png", 1000, atk, Position.x, Position.y, 20, 20, target));
                else /* Wizard */ PS->launchBullet(new Bullet("bullet/fire.png", 600, atk, Position.x, Position.y, 20, 20, target, true));
            } else {
                target->beTargeted.erase(this);
                go();
            }
        } else {
            go();
        }
    } else if (target) {
        target->beTargeted.erase(this);
        go();
    } else go();
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
void Army::go() {
    if (target) {
        target->beTargeted.insert(this);
        if (Position.x <= 975 && Position.x >= 825 && 
                ((Position.y >= 250 && Position.y <= 300) || (Position.y >= 800 && Position.y <= 850))) {
            Position.x -= speed;
        } else if (Position.x >= 975 && target->Position.x < 975) {
            goToBridge();
        } else {
            Position.x += cos(findAngle(Position, target->Position)) * speed;
            Position.y += sin(findAngle(Position, target->Position)) * speed;
        }
    } else {
        if (Position.x <= 980 && Position.x >= 825 &&       // 提前 5 格判斷, 猜測bug原因爲float不夠精準導致findAngle()分母為0
                ((Position.y >= 250 && Position.y <= 300) || (Position.y >= 800 && Position.y <= 850))) {
            Position.x -= speed;    // 遇橋直走
        } else if (Position.x >= 950) {
            goToBridge();
        } else {
            goToTower();
        }
    }
}
void Army::goToBridge() {
    if (Position.y <= PlayScene::MapDiff + PlayScene::BlockSize * PlayScene::MapBlockHeight / 2) {
        Position.x += cos(findAngle(Position, Engine::Point(975, 275))) * speed;
        Position.y += sin(findAngle(Position, Engine::Point(975, 275))) * speed;
    } else {
        Position.x += cos(findAngle(Position, Engine::Point(975, 825))) * speed;
        Position.y += sin(findAngle(Position, Engine::Point(975, 825))) * speed;
    }
}
void Army::goToTower() {
    if(Position.x<=530) return; // have moved to tower  // 完成Tower轉Army即可刪除
    if (Position.y <= PlayScene::MapDiff + PlayScene::BlockSize * PlayScene::MapBlockHeight / 2) {
        Position.x += cos(findAngle(Position, Engine::Point(525, 275))) * speed;
        Position.y += sin(findAngle(Position, Engine::Point(525, 275))) * speed;
    } else {
        Position.x += cos(findAngle(Position, Engine::Point(525, 825))) * speed;
        Position.y += sin(findAngle(Position, Engine::Point(525, 825))) * speed;
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
    if (shortestDistance < detectRadius) return tmpTarget;
    else return nullptr;
}