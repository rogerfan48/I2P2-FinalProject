#ifndef CIRCLEBORDER_HPP
#define CIRCLEBORDER_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"

namespace Engine {
	/// A simple static rectangle object.
	class CircleBorder : public IObject {
	public:
		bool Enable;
        float thickness;
		ALLEGRO_COLOR color;

		explicit CircleBorder(float x, float y, float r, ALLEGRO_COLOR color, float thickness);
		void Draw() const override;
	};
}
#endif
