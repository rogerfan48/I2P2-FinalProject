#include "Circle.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	Circle::Circle(float x, float y, float r, ALLEGRO_COLOR color) :
		IObject(x, y, r, r, 0, 0), color(color), Enable(true) {}
	void Circle::Draw() const {
		if (Enable) 
			al_draw_filled_circle(Position.x, Position.y, Size.x, color);
	}
}
