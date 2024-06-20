#include "RectangleBorder.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	RectangleBorder::RectangleBorder(float x, float y, float w, float h, ALLEGRO_COLOR color, float thickness) :
		IObject(x, y, w, h, 0.5, 0.5), color(color), thickness(thickness), Enable(true) {}
	void RectangleBorder::Draw() const {
		if (Enable) 
			al_draw_rectangle(Position.x, Position.y, Position.x + Size.x, Position.y + Size.y, color, thickness);
	}
}
