#include <functional>
#include <memory>

#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Rectangle.hpp"
#include "RectangleButton.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	RectangleButton::RectangleButton(float x, float y, float w, float h, float r, float g, float b) :
		Rectangle(x, y, w, h, r, g, b) {
            color_origin = al_map_rgb(r, g, b);
			Point mouse = GameEngine::GetInstance().GetMousePosition();
			if (Enabled && (mouse.x >= x && mouse.x <= x + w && mouse.y >= y && mouse.y <= y + h)) {
                color = al_map_rgb(200, 200, 255);
            }
			else {
                color = color_origin;
            }
		}
	void RectangleButton::SetOnClickCallback(std::function<void(void)> onClickCallback) {
		OnClickCallback = onClickCallback;
	}
	void RectangleButton::OnMouseDown(int button, int mx, int my) {
		if ((button & 1) && mouseIn && Enabled) {
			if (OnClickCallback) OnClickCallback();
		}
	}
	void RectangleButton::OnMouseMove(int mx, int my) {
		if (Enabled && (mx >= Position.x && mx <= Position.x + Size.x && my >= Position.x && my <= Position.y + Size.y)) {
			color = al_map_rgb(200, 200, 255);
		}
		else {
			color = color_origin;
		}
	}
}
