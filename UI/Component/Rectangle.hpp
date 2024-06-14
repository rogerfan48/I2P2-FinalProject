#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// <summary>
	/// A simple static rectangle object.
	/// </summary>
	class Rectangle : public IObject {
	public:
		// Smart pointer to bitmap.
		int r, g, b;
		/// <summary>
		/// Construct a rectangle object.
		/// </summary>
		/// <param name="img">The rectangle path in 'Resource/rectangles/'</param>
		/// <param name="x">X-coordinate.</param>
		/// <param name="y">Y-coordinate.</param>
		/// <param name="w">Width of the rectangle, 0 indicates original size.</param>
		/// <param name="h">Height of the rectangle, 0 indicates original size.</param>
		/// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
		/// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
		explicit Rectangle(float x, float y, float w = 0, float h = 0,  float r = 0, float g = 0, float b = 0);
		/// <summary>
		/// Draw the loaded rectangle.
		/// </summary>
		void Draw() const override;
	};
}
#endif
