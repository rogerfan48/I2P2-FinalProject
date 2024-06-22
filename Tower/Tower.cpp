#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "Engine/GameEngine.hpp"
#include "Engine/Resources.hpp"
#include "Tower.hpp"

Tower::Tower(int id, int instanceID, float xB, float yB, int hp, int atk, float cd, float atkRadius, float picRadiusBk, int faction, bool enabled):
	Army(id, instanceID, xB, yB, "Tower", true, hp, atk, cd, 0, atkRadius, atkRadius, picRadiusBk, faction, 1), enabled(enabled) {}

void Tower::Draw() const {
	if (enabled) {
		al_draw_scaled_bitmap(towerImage.get(), 0, 0, al_get_bitmap_width(towerImage.get()), al_get_bitmap_height(towerImage.get()),
			Position.x-picRadiusPx, Position.y-picRadiusPx, 2*picRadiusPx, 2*picRadiusPx, 0);
		al_draw_filled_rectangle(Position.x-picRadiusPx + 5, Position.y-picRadiusPx + 5, 
			Position.x+picRadiusPx - 5, Position.y-picRadiusPx + 10, al_map_rgb(30, 30, 30));
		al_draw_filled_rectangle(Position.x-picRadiusPx + 6, Position.y-picRadiusPx + 6, 
			Position.x-picRadiusPx+6+((countDown)?(1-countDown/coolDown)*(2*picRadiusPx-12):2*picRadiusPx-12), Position.y-picRadiusPx + 9, (faction?redCdColor:blueCdColor));
	} else {
		al_draw_scaled_bitmap(sleepTowerImage.get(), 0, 0, al_get_bitmap_width(sleepTowerImage.get()), al_get_bitmap_height(sleepTowerImage.get()),
			Position.x-picRadiusPx, Position.y-picRadiusPx, 2*picRadiusPx, 2*picRadiusPx, 0);
	}
	
    al_draw_filled_rectangle(Position.x-picRadiusPx + 5, Position.y+picRadiusPx - 25, 
		Position.x+picRadiusPx - 5, Position.y+picRadiusPx - 5, al_map_rgb(30, 30, 30));
	al_draw_filled_rectangle(Position.x-picRadiusPx + 8, Position.y+picRadiusPx - 22,
        Position.x-picRadiusPx+8+std::max(0.0f,hp)/hpMax*(2*picRadiusPx-16), Position.y+picRadiusPx - 8, (faction?redBlood:blueBlood));
	al_draw_text(Engine::Resources::GetInstance().GetFont("recharge.otf",24).get(), Black, 
		Position.x-picRadiusPx+12+2, Position.y+picRadiusPx-38, ALLEGRO_ALIGN_LEFT, std::to_string((int)hp).c_str());
	al_draw_text(Engine::Resources::GetInstance().GetFont("recharge.otf",24).get(), Black, 
		Position.x-picRadiusPx+12-2, Position.y+picRadiusPx-38, ALLEGRO_ALIGN_LEFT, std::to_string((int)hp).c_str());
	al_draw_text(Engine::Resources::GetInstance().GetFont("recharge.otf",24).get(), Black, 
		Position.x-picRadiusPx+12, Position.y+picRadiusPx-38+2, ALLEGRO_ALIGN_LEFT, std::to_string((int)hp).c_str());
	al_draw_text(Engine::Resources::GetInstance().GetFont("recharge.otf",24).get(), Black, 
		Position.x-picRadiusPx+12, Position.y+picRadiusPx-38-2, ALLEGRO_ALIGN_LEFT, std::to_string((int)hp).c_str());
	al_draw_text(Engine::Resources::GetInstance().GetFont("recharge.otf",24).get(), White, 
		Position.x-picRadiusPx+12, Position.y+picRadiusPx-38, ALLEGRO_ALIGN_LEFT, std::to_string((int)hp).c_str());
}
