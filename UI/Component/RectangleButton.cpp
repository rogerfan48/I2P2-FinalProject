#include <functional>
#include <memory>

#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Rectangle.hpp"
#include "RectangleButton.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	RectangleButton::RectangleButton(float x, float y, float w, float h, ALLEGRO_COLOR colorOrigin, ALLEGRO_COLOR colorHovered) :
		Rectangle(x, y, w, h, color), colorOrigin(colorOrigin), colorHovered(colorHovered) {
			Point mouse = GameEngine::GetInstance().GetMousePosition();
			mouseIn = Engine::Collider::IsPointInRect(Engine::Point(mouse.x, mouse.y), Position, Size);
			if (Enabled && mouseIn) color = colorHovered;
			else color = colorOrigin;
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
		mouseIn = Engine::Collider::IsPointInRect(Engine::Point(mx, my), Position, Size);
		if (Enabled && mouseIn) color = colorHovered;
		else color = colorOrigin;
	}
}
