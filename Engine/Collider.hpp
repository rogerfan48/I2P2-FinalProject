#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <allegro5/bitmap.h>
#include <memory>

namespace Engine {
	struct Point;
	/// Helper class for calculating physical collision, overlap, point in region.
	/// Note: Implementing a physical engine is an overkill in this game, helper class is much simpler.
	struct Collider final {
		explicit Collider() = delete;
		/// Check if the bitmap pixel is opaque. (non-transparent)
		/// pntThe pixel coordinate.
		/// bmpThe target bitmap.
		/// return: Determines whether the pixel of the bitmap is opaque.
		static bool IsPointInBitmap(Point pnt, const std::shared_ptr<ALLEGRO_BITMAP>& bmp);
		/// Check if point is within rectangle region.
		/// pntThe point we want to detect.
		/// rectPosThe rectangle left-upper position.
		/// rectSizeThe rectangle size. (width, height)
		/// return: Determines whether the pixel is in the rectangle.
		static bool IsPointInRect(Point pnt, Point rectPos, Point rectSize);
		/// Check if two rectangle overlaps.
		/// rect1p1Top-Left coordinate of the first rectangle.
		/// rect1p2Bottom-Right coordinate of the first rectangle.
		/// rect2p1Top-Left coordinate of the second rectangle.
		/// rect2p2Bottom-Right coordinate of the second rectangle.
		/// return: Determines whether the two rectangles overlaps.
		static bool IsRectOverlap(Point rect1p1, Point rect1p2, Point rect2p1, Point rect2p2);
		/// Check if two circle overlaps.
		/// c1The center coordinate of the first circle.
		/// r1The radius of the first circle.
		/// c2The center coordinate of the second circle.
		/// r2The radius of the second circle.
		/// return: Determines whether the two circles overlaps.
		static bool IsCircleOverlap(Point c1, float r1, Point c2, float r2);
	};
}
#endif // COLLIDER_HPP
