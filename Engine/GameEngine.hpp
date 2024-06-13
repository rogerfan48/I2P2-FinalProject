#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP
#include <allegro5/allegro.h>
#include <string>
#include <unordered_map>

#include "Point.hpp"

/// All general classes are under this namespace for clarity.
namespace Engine {
	class IScene;
	/// The one and only GameEngine for the entire program. Responsible for low-level initialization and window events.
	class GameEngine final {
	private:
		// Allegro5 settings, frames per second, screen width, screen height, maximum simultaneous audio samples.
		int fps{}, screenW{}, screenH{}, reserveSamples{};
		// Determines whether to free memory between scenes.
		bool freeMemoryOnSceneChanged{};
		// Max delta time for update multiplier. If delta time exceeds this threshold, lag occurs.
		float deltaTimeThreshold{};
		// All scenes are stored in hash table for easy access.
		std::unordered_map<std::string, IScene*> scenes;
		// The active scene that occupies the game's update, draw and various events.
		IScene* activeScene{};
		// Allegro5 display for window creation.
		ALLEGRO_DISPLAY* display{};
		// Allegro5 event queue.
		ALLEGRO_EVENT_QUEUE* event_queue{};
		// Allegro5 timer to inject update & draw event into the event queue.
		ALLEGRO_TIMER* update_timer{};
		// The window's title text.
		const char* title{};
		// The window's icon.
		const char* icon{};
		// The scene to change to at next update.
		std::string nextScene{};

		/// Initialize allegro5 library. Creates game window & event queue,
		/// install peripherals and initialize add-ons.
		void initAllegro5();
		/// Process events inside the event queue using an infinity loop,
		/// exit when close button clicked.
		void startEventLoop();
		/// Delegate the update event to the active scene.
		/// deltaTime: Time elapsed since last update, can be used to calculate value changes.
		void update(float deltaTime);
		/// Delegate the draw event to the active scene.
		void draw() const;
		/// Release Allegro5 resources, and free all allocated scenes.
		void destroy();
		/// Private constructor since this class is a Singleton.
		/// Note: Singleton is a class that will only be instantiated once (single instance).
		/// Reference: Design Patterns - Singleton.
		explicit GameEngine() = default;
		/// Change to another scene. Must return immediately and stop using anything initialized in
		/// the scene. Since this call destroys everything initialized.
		/// name: The name of the scene you want to change to.
		void changeScene(const std::string& name);
	public:
		// Note: We'll ignore C++11's move constructor, move assignment operator in this project for simplicity.
		/// Copy constructor is deleted, no copying allowed.
		GameEngine(GameEngine const&) = delete;
		/// Copy assignment operator is deleted, no copy assignment allowed.
		GameEngine& operator=(GameEngine const&) = delete;
		/// Start the game loop until exit, scenes should be added before starting.
		/// firstSceneName: The scene name of the first scene of the game.
		/// fps: The target frame per seconds of the game.
		/// screenW: Window screen width.
		/// screenH: Window screen height.
		/// reserveSamples: Maximum simultaneous audio samples.
		/// title: Window's title text.
		/// icon: Window's icon image path.
		/// freeMemoryOnSceneChanged: Determines whether to free memory between scenes.
		void Start( const std::string& firstSceneName, int fps = 60, int screenW = 600, int screenH = 1200, int reserveSamples = 1000,
					const char* title = "Arena Legends",
					const char* icon = "icon.png", bool freeMemoryOnSceneChanged = false,
					float deltaTimeThreshold = 0.05);
		/// Add a new scene to the game. Should only be called once for each scene.
		/// Use inline-new when adding scene in order to support polymorphism,
		/// The added scenes will be deleted by GameEngine at game end.
		/// name: The unique name of your scene for later access.
		/// scene: The pointer to the scene you want to add.
		void AddNewScene(const std::string& name, IScene* scene);
		/// Change to another scene. The scene will be changed at next update.
		/// name: The name of the scene you want to change to.
		void ChangeScene(const std::string& name);
		/// Get the pointer of the active scene.
		/// return: Pointer to active scene.
		IScene* GetActiveScene() const;
		/// Get scene by name.
		/// name: The scene's name.
		/// return: Pointer to scene.
		IScene* GetScene(const std::string& name);
		/// Get screen size.
		/// return: Screen size.
		Point GetScreenSize() const;
		/// Get screen width.
		/// return: Screen width.
		int GetScreenWidth() const;
		/// Get screen height.
		/// return: Screen height.
		int GetScreenHeight() const;
		/// Get mouse position.
		/// return: Get mouse position.
		Point GetMousePosition() const;
		/// Get key state.
		/// return: Returns whether key is down or not.
		bool IsKeyDown(int keyCode) const;
		/// Typical function to retrieve Singleton instance and supports lazy initialization.
		/// return: The Singleton instance of GameEngine.
		static GameEngine& GetInstance();
	};
}
#endif // GAMEENGINE_HPP
