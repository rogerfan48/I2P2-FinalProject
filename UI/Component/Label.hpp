#ifndef LABEL_HPP
#define LABEL_HPP
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// A simple static text object.
	class Label : public IObject {
	protected:
	public:
		bool Enable;
		// Text to draw.
		std::string Text;
		// Smart pointer to font.
		std::shared_ptr<ALLEGRO_FONT> font;
		// Text's color.
		ALLEGRO_COLOR Color;
		/// Construct a label object.
		/// text: Text to draw.
		/// font: Font to draw in.
		/// fontSize: Text's font size.
		/// x: X-coordinate.
		/// y: Y-coordinate.
		/// r: Color's red value.
		/// g: Color's green value.
		/// b: Color's blue value.
		/// a: Color's alpha value.
		/// anchorX: The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// anchorY: The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		explicit Label(const std::string& text, const std::string& font, int fontSize, float x, float y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 0, bool enable=1);
		/// Draw text with loaded font.
		void Draw() const override;
		/// Return text width.
		/// return: Width of the text.
		int GetTextWidth() const;
		/// Return text height.
		/// return: Height of the text.
		int GetTextHeight() const;
	};
}

#endif // LABEL_HPP
