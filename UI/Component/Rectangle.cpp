#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Rectangle.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	Rectangle::Rectangle(float x, float y, float w, float h, float r, float g, float b) :
		IObject(x, y, w, h, 0.5, 0.5), r(r), g(g), b(b) {}
	void Rectangle::Draw() const {
		al_draw_filled_rectangle(Position.x, Position.y, 
            Position.x + Size.x, Position.y + Size.y, al_map_rgb(r, g, b));
	}
}
