#include "CircleBorder.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	CircleBorder::CircleBorder(float x, float y, float r, ALLEGRO_COLOR color, float thickness) :
		IObject(x, y, r, r, 0, 0), color(color), thickness(thickness), Enable(true) {}
	void CircleBorder::Draw() const {
		if (Enable) 
			al_draw_circle(Position.x, Position.y, Size.x, color, thickness);
	}
}
