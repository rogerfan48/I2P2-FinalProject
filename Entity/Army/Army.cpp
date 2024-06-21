#include "Army.hpp"
#include <allegro5/allegro.h>

#include "Engine/Point.hpp"
#include "Helper/Helper.hpp"
#include "Scene/PlayScene.hpp"

Army::Army(int id, int instanceID, float xB, float yB, std::string Name,
    int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, float picRadiusBk): 
        IObject(xB, yB), ID(id), instanceID(instanceID), Name(Name), 
        hp(hp), hpMax(hp), atk(atk), coolDown(coolDown), speed(speed), speedOri(speed), atkRadius(atkRadius), detectRadius(detectRadius), picRadiusPx(picRadiusBk*PlayScene::BlockSize) {
            Position = blockToPx(Engine::Point(xB, yB));
            Position.x += PlayScene::BlockSize/2;
            Position.y += PlayScene::BlockSize/2;
            head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        }

void Army::Draw() const {
    al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
        Position.x-picRadiusPx, Position.y-picRadiusPx, 2*picRadiusPx, 2*picRadiusPx, 0);
}