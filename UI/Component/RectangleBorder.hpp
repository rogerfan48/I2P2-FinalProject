#ifndef RECTANGLEBORDER_HPP
#define RECTANGLEBORDER_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// A simple static rectangle object.
	class RectangleBorder : public IObject {
	public:
		bool Enable;
        float thickness;
		ALLEGRO_COLOR color;

		explicit RectangleBorder(float x, float y, float w, float h, ALLEGRO_COLOR color, float thickness);
		void Draw() const override;
	};
}
#endif
