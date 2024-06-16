#include "Card.hpp"
#include <allegro5/bitmap.h>

#include "Engine/Resources.hpp"

const int Card::CardWidth = 350;
const int Card::CardHeight = 250;
const int Card::HeadDiameter = 150;

Card::Card(bool selected, float x, float y, std::string Name, std::string Description,
    int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost) :
    Engine::IObject(x, y, CardWidth, CardHeight), cardType(ARMY), Name(Name), Description(Description),
    hp(hp), atk(atk), coolDown(coolDown), speed(speed), 
    atkRadius(atkRadius), detectRadius(detectRadius), count(count), cost(cost),
    hovered(false), selected(selected) {
        bg = Engine::Resources::GetInstance().GetBitmap("card/ArmyCard.png");
        head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        fontName = Engine::Resources::GetInstance().GetFont("recharge.otf", 36);
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 28);
    }

Card::Card(bool selected, float x, float y, std::string Name, std::string Description, int pt, float radius, float time): 
    Engine::IObject(x, y, CardWidth, CardHeight), cardType(SPELL), Name(Name), Description(Description),
    pt(pt), radius(radius), time(time),
    hovered(false), selected(selected) {
        bg = Engine::Resources::GetInstance().GetBitmap("card/SpellCard.png");
        head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        fontName = Engine::Resources::GetInstance().GetFont("recharge.otf", 36);
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 24);
    }

void Card::Draw() const {
    if (!hovered) {
        al_draw_scaled_bitmap(bg.get(), 0, 0, al_get_bitmap_width(bg.get()), al_get_bitmap_height(bg.get()),
            Position.x, Position.y, Size.x, Size.y, 0);
        al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
            Position.x+25, Position.y+75, HeadDiameter, HeadDiameter, 0);
        al_draw_text(fontName.get(), White, Position.x+30, Position.y+20, 0, Name.c_str());
    }
}