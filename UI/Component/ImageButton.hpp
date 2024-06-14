#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP
#include <allegro5/bitmap.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/IControl.hpp"
#include "Image.hpp"

namespace Engine {
	/// A clickable button, changes image when mouse move.
	class ImageButton: public Image, public IControl {
	protected:
		// Determines whether mouse is in the button.
		bool mouseIn = false;
		// The smart pointer that points to bitmap for mouse-out display.
		std::shared_ptr<ALLEGRO_BITMAP> imgOut;
		// The smart pointer that points to bitmap for mouse-in display.
		std::shared_ptr<ALLEGRO_BITMAP> imgIn;
		// The callback function to call when button clicked.
		std::function<void()> OnClickCallback;
	public:
		// Whether the button can be pressed.
		bool Enabled = true;
		/// Construct a image object.
		/// img: The mouse-out image path in 'Resource/images/'
		/// imgIn: The mouse-in image path in 'Resource/images/'
		/// x: X-coordinate.
		/// y: Y-coordinate.
		/// w: Width of the image, 0 indicates original size.
		/// h: Height of the image, 0 indicates original size.
		/// anchorX: The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// anchorY: The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		explicit ImageButton(std::string img, std::string imgIn, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
		/// Set the callback function when clicked.
		/// onClickCallback: 
		void SetOnClickCallback(std::function<void(void)> onClickCallback);
		/// Delegated from scene when mouse button down.
		/// button: The button pressed.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		void OnMouseDown(int button, int mx, int my) override;
		/// Delegated from scene when mouse move.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		void OnMouseMove(int mx, int my) override;
	};
}
#endif // IMAGEBUTTON_HPP
