#include "Card.hpp"
#include <allegro5/bitmap.h>
#include <allegro5/allegro_primitives.h>
#include <string>

#include "Engine/Resources.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Collider.hpp"
#include "Scene/CardSetScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Helper/Helper.hpp"

const int Card::CardWidth = 350;
const int Card::CardHeight = 250;
const int Card::HeadDiameter = 150;
const int Card::diff = 5;
const int Card::CardWidthP = 380;
const int Card::CardHeightP = 280;
const int Card::HeadDiameterP = 180;
const int Card::ElixirWidth = 60;

// Army/Spell in CardSetScene
Card::Card(bool selected, int id, float x, float y, std::string Name, std::string Description,
    int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost) :
    Engine::IObject(x, y, CardWidth, CardHeight), cardType(ARMY), ID(id), Name(Name), Description(Description),
    hp(hp), atk(atk), coolDown(coolDown), speed(speed), 
    atkRadius(atkRadius), detectRadius(detectRadius), count(count), cost(cost), selected(selected), inPlay(false) {
        bg = Engine::Resources::GetInstance().GetBitmap("card/ArmyCard.png");
        head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        elixir = Engine::Resources::GetInstance().GetBitmap("elixir.png");
        fontName = Engine::Resources::GetInstance().GetFont("recharge.otf", 36);
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 20);
        fontDescH = Engine::Resources::GetInstance().GetFont("recharge.otf", 21);
        fontBelow = Engine::Resources::GetInstance().GetFont("recharge.otf", 40);
        fontElixir = Engine::Resources::GetInstance().GetFont("recharge.otf", 32);
        fontElixirOuter = Engine::Resources::GetInstance().GetFont("recharge.otf", 38);

        Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();
        hovered = Engine::Collider::IsPointInRect(mouse, Position, Size);
    }
Card::Card(bool selected, int id, float x, float y, std::string Name, std::string Description, int pt, float radius, float duration, float interval, int atkTower, int cost): 
    Engine::IObject(x, y, CardWidth, CardHeight), cardType(SPELL), ID(id), Name(Name), Description(Description),
    pt(pt), radius(radius), duration(duration), interval(interval), atkTower(atkTower), cost(cost), selected(selected), inPlay(false) {
        bg = Engine::Resources::GetInstance().GetBitmap("card/SpellCard.png");
        head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        elixir = Engine::Resources::GetInstance().GetBitmap("elixir.png");
        fontName = Engine::Resources::GetInstance().GetFont("recharge.otf", 40);
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 20);
        fontDescH = Engine::Resources::GetInstance().GetFont("recharge.otf", 21);
        fontBelow = Engine::Resources::GetInstance().GetFont("recharge.otf", 40);
        fontElixir = Engine::Resources::GetInstance().GetFont("recharge.otf", 32);
        fontElixirOuter = Engine::Resources::GetInstance().GetFont("recharge.otf", 38);

        Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();
        hovered = Engine::Collider::IsPointInRect(mouse, Position, Size);
    }

// Army/Spell in PlayScene
Card::Card(int id, float x, float y, std::string Name,
    int hp, int atk, float coolDown, float speed, float atkRadius, float detectRadius, int count, int cost) :
    Engine::IObject(x, y, CardWidthP, CardHeightP), cardType(ARMY), ID(id), Name(Name),
    hp(hp), atk(atk), coolDown(coolDown), speed(speed), 
    atkRadius(atkRadius), detectRadius(detectRadius), count(count), cost(cost), selected(false), inPlay(true) {
        bg = Engine::Resources::GetInstance().GetBitmap("card/ArmyCard.png");
        head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        elixir = Engine::Resources::GetInstance().GetBitmap("elixir.png");
        fontName = Engine::Resources::GetInstance().GetFont("recharge.otf", 36);
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 22);
        fontDescH = Engine::Resources::GetInstance().GetFont("recharge.otf", 23);
        fontElixir = Engine::Resources::GetInstance().GetFont("recharge.otf", 32);
        fontElixirOuter = Engine::Resources::GetInstance().GetFont("recharge.otf", 38);

        Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();
        hovered = Engine::Collider::IsPointInRect(mouse, Position, Size);
    }
Card::Card(int id, float x, float y, std::string Name, int pt, float radius, float duration, float interval, int atkTower, int cost): 
    Engine::IObject(x, y, CardWidthP, CardHeightP), cardType(SPELL), ID(id), Name(Name),
    pt(pt), radius(radius), duration(duration), interval(interval), atkTower(atkTower), cost(cost), selected(false), inPlay(true) {
        bg = Engine::Resources::GetInstance().GetBitmap("card/SpellCard.png");
        head = Engine::Resources::GetInstance().GetBitmap("card/"+Name+".png");
        elixir = Engine::Resources::GetInstance().GetBitmap("elixir.png");
        fontName = Engine::Resources::GetInstance().GetFont("recharge.otf", 40);
        fontDesc = Engine::Resources::GetInstance().GetFont("recharge.otf", 22);
        fontDescH = Engine::Resources::GetInstance().GetFont("recharge.otf", 23);
        fontElixir = Engine::Resources::GetInstance().GetFont("recharge.otf", 32);
        fontElixirOuter = Engine::Resources::GetInstance().GetFont("recharge.otf", 38);

        Engine::Point mouse = Engine::GameEngine::GetInstance().GetMousePosition();
        hovered = Engine::Collider::IsPointInRect(mouse, Position, Size);
    }

void Card::Draw() const {
    if (!inPlay) {
        if (!hovered) {
            if (selected) al_draw_filled_rectangle(Position.x-5, Position.y-5, Position.x+Size.x+5, Position.y+Size.y+5, White);
            al_draw_scaled_bitmap(bg.get(), 0, 0, al_get_bitmap_width(bg.get()), al_get_bitmap_height(bg.get()),
                Position.x, Position.y, Size.x, Size.y, 0);
            al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
                Position.x+25, Position.y+75, HeadDiameter, HeadDiameter, 0);
            al_draw_text(fontName.get(), White, Position.x+30, Position.y+20, 0, Name.c_str());
            al_draw_scaled_bitmap(elixir.get(), 0, 0, al_get_bitmap_width(elixir.get()), al_get_bitmap_height(elixir.get()),
                Position.x+280, Position.y+10, ElixirWidth, ElixirWidth, 0);
            auto fe = fontElixir.get();
            auto cs = std::to_string(cost);
            auto ct = cs.c_str();
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2-2, Position.y-al_get_font_line_height(fe)/2+39, 0, ct);
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2+2, Position.y-al_get_font_line_height(fe)/2+39, 0, ct);
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2, Position.y-al_get_font_line_height(fe)/2+39-2, 0, ct);
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2, Position.y-al_get_font_line_height(fe)/2+39+2, 0, ct);
            al_draw_text(fe, White, Position.x+311-al_get_text_width(fe, ct)/2, Position.y-al_get_font_line_height(fe)/2+39, 0, ct);
            if (cardType == ARMY) {
                al_draw_text(fontDesc.get(), White, Position.x+200, Position.y+90, 0, ("HP: "+std::to_string(hp)).c_str());
                al_draw_text(fontDesc.get(), White, Position.x+200, Position.y+125, 0, ("Atk: "+std::to_string(atk)).c_str());
                al_draw_text(fontDesc.get(), White, Position.x+200, Position.y+160, 0, ("CD: "+floatToStr(coolDown)).c_str());
                al_draw_text(fontDesc.get(), White, Position.x+200, Position.y+195, 0, ("Count: "+std::to_string(count)).c_str());
            }
        } else {
            Engine::Point nP(Position); nP.x-=diff; nP.y-=diff;
            Engine::Point nS(Size); nS.x+=2*diff; nS.y+=2*diff;
            if (selected) al_draw_filled_rectangle(nP.x-5, nP.y-5, nP.x+nS.x+5, nP.y+nS.y+5, White);
            al_draw_scaled_bitmap(bg.get(), 0, 0, al_get_bitmap_width(bg.get()), al_get_bitmap_height(bg.get()),
                nP.x, nP.y, nS.x, nS.y, 0);
            al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
                nP.x+25, nP.y+75, HeadDiameter+2*diff, HeadDiameter+2*diff, 0);
            al_draw_text(fontName.get(), White, nP.x+30, nP.y+20, 0, Name.c_str());
            al_draw_scaled_bitmap(elixir.get(), 0, 0, al_get_bitmap_width(elixir.get()), al_get_bitmap_height(elixir.get()),
                Position.x+280+diff/2, Position.y+10-diff/2, ElixirWidth, ElixirWidth, 0);
            auto fe = fontElixir.get();
            auto cs = std::to_string(cost);
            auto ct = cs.c_str();
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2-2+diff/2, Position.y-al_get_font_line_height(fe)/2+39-diff/2, 0, ct);
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2+2+diff/2, Position.y-al_get_font_line_height(fe)/2+39-diff/2, 0, ct);
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2+diff/2, Position.y-al_get_font_line_height(fe)/2+39-2-diff/2, 0, ct);
            al_draw_text(fe, Black, Position.x+311-al_get_text_width(fe, ct)/2+diff/2, Position.y-al_get_font_line_height(fe)/2+39+2-diff/2, 0, ct);
            al_draw_text(fe, White, Position.x+311-al_get_text_width(fe, ct)/2+diff/2, Position.y-al_get_font_line_height(fe)/2+39-diff/2, 0, ct);
            if (cardType == ARMY) {
                al_draw_text(fontDescH.get(), White, nP.x+diff+200, nP.y+diff+90, 0, ("HP: "+std::to_string(hp)).c_str());
                al_draw_text(fontDescH.get(), White, nP.x+diff+200, nP.y+diff+125+2, 0, ("Atk: "+std::to_string(atk)).c_str());
                al_draw_text(fontDescH.get(), White, nP.x+diff+200, nP.y+diff+160+4, 0, ("CD: "+floatToStr(coolDown)).c_str());
                al_draw_text(fontDescH.get(), White, nP.x+diff+200, nP.y+diff+195+6, 0, ("Count: "+std::to_string(count)).c_str());
            }
            al_draw_text(fontBelow.get(), White, 
                Engine::GameEngine::GetInstance().GetScreenSize().x/2-al_get_text_width(fontBelow.get(), Description.c_str())/2, 
                1130-al_get_font_line_height(fontBelow.get())/2, 0, Description.c_str());
        }
    } else {
        if (!hovered) {
            if (selected) al_draw_filled_rectangle(Position.x-5, Position.y-5, Position.x+Size.x+5, Position.y+Size.y+5, White);
            al_draw_scaled_bitmap(bg.get(), 0, 0, al_get_bitmap_width(bg.get()), al_get_bitmap_height(bg.get()),
                Position.x, Position.y, Size.x, Size.y, 0);
            al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
                Position.x+20, Position.y+80, HeadDiameterP, HeadDiameterP, 0);
            al_draw_text(fontName.get(), White, Position.x+30, Position.y+20, 0, Name.c_str());
            al_draw_scaled_bitmap(elixir.get(), 0, 0, al_get_bitmap_width(elixir.get()), al_get_bitmap_height(elixir.get()),
                Position.x+302, Position.y+17, ElixirWidth, ElixirWidth, 0);
            auto fe = fontElixir.get();
            auto cs = std::to_string(cost);
            auto ct = cs.c_str();
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2-2, Position.y-al_get_font_line_height(fe)/2+46, 0, ct);
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2+2, Position.y-al_get_font_line_height(fe)/2+46, 0, ct);
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2, Position.y-al_get_font_line_height(fe)/2+46-2, 0, ct);
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2, Position.y-al_get_font_line_height(fe)/2+46+2, 0, ct);
            al_draw_text(fe, White, Position.x+333-al_get_text_width(fe, ct)/2, Position.y-al_get_font_line_height(fe)/2+46, 0, ct);
            if (cardType == ARMY) {
                al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+90, 0, ("HP: "+std::to_string(hp)).c_str());
                al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+130, 0, ("Atk: "+std::to_string(atk)).c_str());
                al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+170, 0, ("CD: "+floatToStr(coolDown)).c_str());
                al_draw_text(fontDesc.get(), White, Position.x+220, Position.y+210, 0, ("Count: "+std::to_string(count)).c_str());
            }
        } else {
            Engine::Point nP(Position); nP.x-=diff; nP.y-=diff;
            Engine::Point nS(Size); nS.x+=2*diff; nS.y+=2*diff;
            if (selected) al_draw_filled_rectangle(nP.x-5, nP.y-5, nP.x+nS.x+5, nP.y+nS.y+5, White);
            al_draw_scaled_bitmap(bg.get(), 0, 0, al_get_bitmap_width(bg.get()), al_get_bitmap_height(bg.get()),
                nP.x, nP.y, nS.x, nS.y, 0);
            al_draw_scaled_bitmap(head.get(), 0, 0, al_get_bitmap_width(head.get()), al_get_bitmap_height(head.get()),
                nP.x+20, nP.y+80, HeadDiameterP+2*diff, HeadDiameterP+2*diff, 0);
            al_draw_text(fontName.get(), White, nP.x+30, nP.y+20, 0, Name.c_str());
            al_draw_scaled_bitmap(elixir.get(), 0, 0, al_get_bitmap_width(elixir.get()), al_get_bitmap_height(elixir.get()),
                Position.x+302+diff/2, Position.y+17-diff/2, ElixirWidth, ElixirWidth, 0);
            auto fe = fontElixir.get();
            auto cs = std::to_string(cost);
            auto ct = cs.c_str();
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2-2+diff/2, Position.y-al_get_font_line_height(fe)/2+46-diff/2, 0, ct);
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2+2+diff/2, Position.y-al_get_font_line_height(fe)/2+46-diff/2, 0, ct);
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2+diff/2, Position.y-al_get_font_line_height(fe)/2+46-2-diff/2, 0, ct);
            al_draw_text(fe, Black, Position.x+333-al_get_text_width(fe, ct)/2+diff/2, Position.y-al_get_font_line_height(fe)/2+46+2-diff/2, 0, ct);
            al_draw_text(fe, White, Position.x+333-al_get_text_width(fe, ct)/2+diff/2, Position.y-al_get_font_line_height(fe)/2+46-diff/2, 0, ct);
            if (cardType == ARMY) {
                al_draw_text(fontDescH.get(), White, nP.x+diff+220, nP.y+diff+90, 0, ("HP: "+std::to_string(hp)).c_str());
                al_draw_text(fontDescH.get(), White, nP.x+diff+220, nP.y+diff+130+2, 0, ("Atk: "+std::to_string(atk)).c_str());
                al_draw_text(fontDescH.get(), White, nP.x+diff+220, nP.y+diff+170+4, 0, ("CD: "+floatToStr(coolDown)).c_str());
                al_draw_text(fontDescH.get(), White, nP.x+diff+220, nP.y+diff+210+6, 0, ("Count: "+std::to_string(count)).c_str());
            }
        }
    }
}

void Card::OnMouseDown(int button, int mx, int my) {
    if (!inPlay) {
        if ((button & 1) && hovered) {
            CardSetScene* CSC = dynamic_cast<CardSetScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
            selected = !selected;
            if (selected) CSC->newCardSet.insert(ID);
            else CSC->newCardSet.erase(ID);
            CSC->saveButton->Enabled = (CSC->newCardSet.size()==8);
        }
    } else {
        if ((button & 1) && hovered) {
            PlayScene* PS = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
            gameData.A.selectedCard = (Position.x-110)/400;
            for (auto i : PS->cardPointer) i->selected = false;
            selected = true;
            PS->selectedCard = this;
        }
    }
}
void Card::OnMouseMove(int mx, int my) {
	hovered = Engine::Collider::IsPointInRect(Engine::Point(mx, my), Position, Size);
}

void Card::placeArmy(float xB, float yB) {}
Spell* Card::placeSpell(int instanceID, float xB, float yB) { return nullptr; }