#ifndef RECTANGLEBUTTON_HPP
#define RECTANGLEBUTTON_HPP
#include <allegro5/bitmap.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/IControl.hpp"
#include "Rectangle.hpp"

namespace Engine {
	/// A clickable button, changes rectangle when mouse move.
	class RectangleButton: public Rectangle, public IControl {
	protected:
		// Determines whether mouse is in the button.
		bool mouseIn = false;
		// The smart pointer that points to bitmap for mouse-out display.
		std::shared_ptr<ALLEGRO_BITMAP> imgOut;
		// The smart pointer that points to bitmap for mouse-in display.
		std::shared_ptr<ALLEGRO_BITMAP> imgIn;
		// The callback function to call when button clicked.
		std::function<void()> OnClickCallback;
        // Original color
        ALLEGRO_COLOR colorOrigin;
	public:
		// Whether the button can be pressed.
		bool Enabled = true;
		/// Construct a rectangle object.
		/// x: X-coordinate.
		/// y: Y-coordinate.
		/// w: Width of the rectangle, 0 indicates original size.
		/// h: Height of the rectangle, 0 indicates original size.
		explicit RectangleButton(float x, float y, float w, float h, float r, float g, float b);
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
#endif
