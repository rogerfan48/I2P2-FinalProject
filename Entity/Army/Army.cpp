#include "Army.hpp"
#include <allegro5/allegro.h>

#include "Engine/Point.hpp"
#include "Helper/Helper.hpp"
#include "Scene/PlayScene.hpp"

Army::Army(int id, int instanceID, float xB, float yB, std::string Name,
    bool bullet, int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk): 
        IObject(xB, yB), ID(id), instanceID(instanceID), Name(Name), 
        fireBullet(bullet), hp(hp), hpMax(hp), atk(atk), coolDown(coolDown), speed(speed), speedOri(speed), atkRadius(atkRadius), detectRadius(detectRadius), picRadiusPx(picRadiusBk*PlayScene::BlockSize),
        stunned(0), countDown(0), target(nullptr) {
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
    PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    countDown -= deltaTime;
    if (countDown < 0) {
        countDown = coolDown;
        if (target) {
            if ((target->Position-Position).Magnitude() <= atkRadius) {
                if (Name == "Archers") PS->launchBullet(new Bullet("bullet/arrow.png", 800, atk, Position.x, Position.y, 10, 30, target));
                else if (Name == "Musketeer") PS->launchBullet(new Bullet("bullet/bullet.png", 1000, atk, Position.x, Position.y, 20, 20, target));
                else /* Wizard */ PS->launchBullet(new Bullet("bullet/fire.png", 600, atk, Position.x, Position.y, 20, 20, target, true));
            } else if ((target->Position-Position).Magnitude() <= detectRadius) {
                // TODO: move toward target
            } else {
                target->beTargeted.erase(this);
                goto FindAndGo;
            }
        } else {
        FindAndGo:
            target = searchTarget();
            // TODO: move
        }
    }
}

void Army::Healed(float pt) {
    if (hp+pt > hpMax) hp = hpMax;
    else hp += pt;
}
void Army::Damaged(float pt) {
    hp -= pt;
    if (hp < 0) {
        PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        PS->A_ToBeDead.insert(ID);
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