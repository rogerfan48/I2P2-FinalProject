#ifndef GROUP_HPP
#define GROUP_HPP
#include <list>
#include <utility>

#include "IControl.hpp"
#include "IObject.hpp"

namespace Engine {
	/// A ControlObject Group that can contain other objects or controls.
	class Group: public IObject, public IControl {
	protected:
		// Stores all object pointers in the scene.
		// The first boolean indicates whether the scene should delete it.
		std::list<std::pair<bool, IObject*>> objects;
		// Stores all control pointers in the scene.
		// The first boolean indicates whether the scene should delete it.
		std::list<std::pair<bool, IControl*>> controls;
		// Note: Using linked-list and inline-new might cause some serious cache misses,
		//       however this implementation brings us more convenience than the impact
		//       on performance. Trying to deal with cache misses requires complicated code,
		//       so we'll just ignore it for simplicity.
		/// Add Object to scene.
		/// shouldDelete: Indicates whether the scene handle the Object deletion for you.
		/// obj: The Object to add.
		void addObject(bool shouldDelete, IObject* obj);
		/// Add Control to scene.
		/// shouldDelete: Indicates whether the scene handle the Control deletion for you.
		/// ctrl: The Control to add.
		void addControl(bool shouldDelete, IControl* ctrl);
		/// Insert Object to scene before the iterator.
		/// shouldDelete: Indicates whether the scene handle the deletion for you.
		/// obj: The Object to insert.
		/// it: The iterator that the object should insert before.
		void insertObject(bool shouldDelete, IObject* obj, std::list<std::pair<bool, IObject*>>::iterator it);
	public:
		/// Create an empty group.
		explicit Group() = default;
		/// Copy constructor/Copy assignment operator are deleted, no copying/copy assignment allowed.
		Group(Group const&) = delete;
		Group& operator=(Group const&) = delete;
		/// The default virtual destructor to support polymorphism destruction.
		virtual ~Group();
		/// Remove all children (objects and controls).
		void Clear();
		/// Run game logic such as updating the world, checking for collision, and so on.
		/// This is called when the game should update its logic, usually 'fps' times per second.
		/// Delegate the update event to all visible objects.
		/// deltaTime: Time elapsed since last update, can be used to calculate value changes.
		void Update(float deltaTime) override;
		/// Draw to window display.
		/// This is called when the game should redraw the window.
		/// Delegate the draw event to all visible objects.
		void Draw() const override;
		/// Delegate the key down event to all controls.
		/// keyCode: The keycode of pressed key.
		void OnKeyDown(int keyCode) override;
		/// Delegate the key up event to all controls.
		/// keyCode: The keycode of released key.
		void OnKeyUp(int keyCode) override;
		/// Delegate the mouse key down event to all controls.
		/// button: The button pressed.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		void OnMouseDown(int button, int mx, int my) override;
		/// Delegate the mouse key up event to all controls.
		/// button: The button released.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		void OnMouseUp(int button, int mx, int my) override;
		/// Delegate the mouse move event to all controls.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		void OnMouseMove(int mx, int my) override;
		/// Delegate the mouse scroll event to all controls.
		/// mx: Mouse x coordinate in window space.
		/// my: Mouse y coordinate in window space.
		/// delta: Mouse z scroll delta value.
		void OnMouseScroll(int mx, int my, int delta) override;
		/// Remove the Object from this scene.
		/// it: The iterator of the Object.
		void RemoveObject(std::list<std::pair<bool, IObject*>>::iterator it);
		/// Remove the Control from this scene.
		/// it: The iterator of the Control.
		void RemoveControl(std::list<std::pair<bool, IControl*>>::iterator it);
		/// Remove the ControlObject from this scene.
		/// ctrlIt: The iterator of the Control.
		/// objIt: The iterator of the Object.
		void RemoveControlObject(std::list<std::pair<bool, IControl*>>::iterator ctrlIt, std::list<std::pair<bool, IObject*>>::iterator objIt);
		/// Add Object to scene.
		/// Use inline-new when adding Object in order to support polymorphism,
		/// The added objects will be deleted by Scene at remove or terminate.
		/// obj: The Object to add.
		void AddNewObject(IObject* obj);
		/// Insert Object to scene before the iterator.
		/// Use inline-new when adding Object in order to support polymorphism,
		/// The added objects will be deleted by Scene at remove or terminate.
		/// obj: The Object to insert.
		/// it: The iterator that the object should insert before.
		void InsertNewObject(IObject* obj, std::list<std::pair<bool, IObject*>>::iterator it);
		/// Add Control to scene.
		/// Use inline-new when adding Control in order to support polymorphism,
		/// The added controls will be deleted by Scene at remove or terminate.
		/// ctrl: The Control to add.
		void AddNewControl(IControl* ctrl);
		/// Add ControlObject to scene.
		/// Use inline-new when adding ControlObject in order to support polymorphism,
		/// ControlObject means classes that inherit both Control and Object. (e.g. buttons)
		/// ctrl: The ControlObject to add.
		void AddNewControlObject(IControl* ctrl);
		/// Add Object to scene.
		/// Use reference when adding Object. Make sure it won't be deconstructed due to out-of-scope.
		/// The added objects will not be deleted by Scene at remove or terminate.
		/// obj: The Object to add.
		void AddRefObject(IObject& obj);
		/// Insert Object to scene before the iterator.
		/// Use reference when adding Object. Make sure it won't be deconstructed due to out-of-scope.
		/// The added objects will not be deleted by Scene at remove or terminate.
		/// obj: The Object to insert.
		/// it: The iterator that the object should insert before.
		void InsertRefObject(IObject& obj, std::list<std::pair<bool, IObject*>>::iterator it);
		/// Add Control to scene.
		/// Use reference when adding Control. Make sure it won't be deconstructed due to out-of-scope.
		/// The added controls will not be deleted by Scene at remove or terminate.
		/// ctrl: The Control to add.
		void AddRefControl(IControl& ctrl);
		/// Add ControlObject to scene.
		/// Use reference when adding ControlObject. Make sure it won't be deconstructed due to out-of-scope.
		/// The added ControlObjects will not be deleted by Scene at remove or terminate.
		/// ctrl: The ControlObject to add.
		void AddRefControlObject(IControl& ctrl);
		/// Get all objects.
		/// return: A linked-list of all objects contained.
		std::list<IObject*> GetObjects();
		/// Get all controls.
		/// returns: A linked-list of all controls contained.
		std::list<IControl*> GetControls();
	};
}
#endif // GROUP_HPP
