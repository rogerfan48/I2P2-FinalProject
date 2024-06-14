#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// A simple static image object.
	class Image : public IObject {
	public:
		// Smart pointer to bitmap.
		std::shared_ptr<ALLEGRO_BITMAP> bmp;
		/// Construct a image object.
		/// img: The image path in 'Resource/images/'
		/// x: X-coordinate.
		/// y: Y-coordinate.
		/// w: Width of the image, 0 indicates original size.
		/// h: Height of the image, 0 indicates original size.
		/// anchorX: The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// anchorY: The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		explicit Image(std::string img, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
		/// Draw the loaded image.
		void Draw() const override;
		/// Return bitmap width.
		/// return: Width of the original or scaled bitmap.
		int GetBitmapWidth() const;
		/// Return bitmap height.
		/// return: Height of the original or scaled bitmap.
		int GetBitmapHeight() const;
	};
}
#endif // IMAGE_HPP
