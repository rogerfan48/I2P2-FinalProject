#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <allegro5/color.h>
#include <string>

#include "UI/Component/Image.hpp"
#include "Engine/Point.hpp"

namespace Engine {
	/// Image that supports rotation, velocity, tint, and collision radius.
	class Sprite : public Image {
	public:
		// Rotation angle in radians.
		float Rotation;
		// Pixel in seconds.
		Point Velocity;
		// Color tint.
		ALLEGRO_COLOR Tint;
		// Assume a circle is a good approximation of the sprite's boundary.
		float CollisionRadius = 0;
		/// Construct a sprite object.
		/// img: The image path in 'resource/images/'
		/// x: X-coordinate.
		/// y: Y-coordinate.
		/// w: Width of the image, 0 indicates original size.
		/// h: Height of the image, 0 indicates original size.
		/// anchorX: The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// anchorY: The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		/// rotation: Rotation in radians.
		/// vx: X-Velocity.
		/// vy: Y-Velocity.
		/// r: Color tint red value.
		/// g: Color tint green value.
		/// b: Color tint blue value.
		/// a: Color tint alpha value.
		explicit Sprite(std::string img, float x, float y, float w = 0, float h = 0, float anchorX = 0.5f, float anchorY = 0.5f,
			float rotation = 0, float vx = 0, float vy = 0, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
		/// Draw to window display.
		/// This is called when the game should redraw the window.
		void Draw() const override;
		/// Run game logic such as updating the world, checking for collision, and so on.
		/// This is called when the game should update its logic, usually 'fps' times per second.
		/// deltaTime: Time elapsed since last update, can be used to calculate value changes.
		void Update(float deltaTime) override;
	};
}
#endif // SPRITE_HPP

