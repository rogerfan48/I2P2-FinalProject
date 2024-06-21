#ifndef ICONTROL_HPP
#define ICONTROL_HPP
#include <list>
#include <utility>

namespace Engine {
	/// The base interface class for controls that needs to process event callbacks.
	class IControl {
		friend class Group;
	protected:
		// The iterator of controls linked-list when added to scene.
		// Can make removing controls faster.
		std::list<std::pair<bool, IControl*>>::iterator controlIterator{};
		/// The interface cannot be instantiated directly, must be inherited.
		explicit IControl() = default;
	public:
		/// The default virtual destructor to support polymorphism destruction.
		virtual ~IControl() = default;
		/// Copy constructor does not add a new instance to scene, they are still the same object.
		IControl(const IControl& other) = default;
		/// Copy assignment operator does not add a new instance to scene, they are still the same object.
		IControl& operator=(IControl const&) = default;
		std::list<std::pair<bool, IControl*>>::iterator GetControlIterator() const;
		/// Delegated from scene when keyboard key down.
		/// keyCode: The keycode of pressed key.
		virtual void OnKeyDown(int keyCode);
		/// Delegated from scene when keyboard key up.
		/// keyCode: The keycode of released key.
		virtual void OnKeyUp(int keyCode);
		/// Delegated from scene when mouse button down.
		/// button: The button pressed.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		virtual void OnMouseDown(int button, int mx, int my);
		/// Delegated from scene when mouse button up.
		/// button: The button released.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		virtual void OnMouseUp(int button, int mx, int my);
		/// Delegated from scene when mouse move.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		virtual void OnMouseMove(int mx, int my);
		/// Delegated from scene when mouse scroll.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		/// delta: Mouse z scroll delta value.
		virtual void OnMouseScroll(int mx, int my, int delta);
	};
}
#endif // ICONTROL_HPP
