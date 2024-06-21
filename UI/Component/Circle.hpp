#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// A simple static rectangle object.
	class Circle : public IObject {
	public:
		bool Enable;
		// color
		ALLEGRO_COLOR color;
		/// Construct a rectangle object.
		/// x, y: Center of the circle
		/// r: Radius
		explicit Circle(float x, float y, float r, ALLEGRO_COLOR color);
		/// Draw the loaded rectangle.
		void Draw() const override;
	};
}
#endif
