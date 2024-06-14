#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// A simple static rectangle object.
	class Rectangle : public IObject {
	public:
		// color
		int r, g, b;
		/// Construct a rectangle object.
		/// x: X-coordinate.
		/// y: Y-coordinate.
		/// w: Width of the rectangle, 0 indicates original size.
		/// h: Height of the rectangle, 0 indicates original size.
		/// anchorX: The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// anchorY: The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		explicit Rectangle(float x, float y, float w = 0, float h = 0,  float r = 0, float g = 0, float b = 0);
		/// Draw the loaded rectangle.
		void Draw() const override;
	};
}
#endif
