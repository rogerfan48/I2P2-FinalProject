#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include <allegro5/bitmap.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <memory>
#include <string>
#include <unordered_map>


namespace Engine {
	/// The one and only Resources for the entire program. Responsible for low-level resource loading and destroying.
	/// It acts like a smart caching helper class.
	class Resources final {
	private:
		// The path prefix for loading bitmaps/fonts/samples.
		static const std::string bitmapPathPrefix;
		static const std::string fontPathPrefix;
		static const std::string samplePathPrefix;
		// All bitmaps/fonts/samples are stored in hash table for easy access and management.
		// Note: std::shared_ptr is a kind of smart pointer.
		//       To put it simple, it's a pointer that will delete itself when no one has reference to it.
		//       It's very convenient, and can greatly reduce the possibility of memory leaks if used correctly.
		//       If you have heard of Garbage Collection, the concept is almost the same. However, smart pointers are faster,
		//       and only relies on reference counting and class destructor, which I think is really "smart".
		// Note (Advanced): The reason we didn't use std::weak_ptr here is to avoid the possibility of some resource
		//                  being loaded and destroyed consecutively, which could occur if a object prototype being
		//                  added, removed, added, removed, ... in the same scene (e.g. bullets).
		// Reference: Smart Pointers - std::unique_ptr, std::shared_ptr, std::weak_ptr.
		std::unordered_map<std::string, std::shared_ptr<ALLEGRO_BITMAP>> bitmaps;
		std::unordered_map<std::string, std::shared_ptr<ALLEGRO_FONT>> fonts;
		std::unordered_map<std::string, std::shared_ptr<ALLEGRO_SAMPLE>> samples;
		// All (sample instance, sample) pairs are stored in hash table for easy access and management.
		std::unordered_map<std::string, std::pair<std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>, std::shared_ptr<ALLEGRO_SAMPLE>>> sample_instance_pairs;
		/// Private constructor since this class is a Singleton.
		explicit Resources();
	public:
		/// Copy constructor is deleted, no copying allowed.
		Resources(Resources const&) = delete;
		/// Copy assignment operator is deleted, no copy assignment allowed.
		void operator=(Resources const&) = delete;
		/// Release all loaded resources.
		~Resources();
		/// Release resources that are not currently used.
		void ReleaseUnused();
		/// Get bitmap pointer by name. The file should be put under "resource/images/".
		/// name: The filename of the image. (Including extension)
		/// return: The smart pointer of the bitmap.
		std::shared_ptr<ALLEGRO_BITMAP> GetBitmap(std::string name);
		/// Get bitmap pointer by name, and resize it. The file should be put under "resource/images/".
		/// name: The filename of the image. (Including extension)
		/// width: The target width that we want the image to be resized to.
		/// height: The target height that we want the image to be resized to.
		/// return: The smart pointer of the bitmap.
		std::shared_ptr<ALLEGRO_BITMAP> GetBitmap(std::string name, int width, int height);
		/// Get font pointer by name. The file should be put under "resource/fonts/".
		/// name: The filename of the font. (Including extension)
		/// size: The font size of the font.
		/// return: The smart pointer of the font.
		std::shared_ptr<ALLEGRO_FONT> GetFont(std::string name, int fontSize);
		/// Get sample pointer by name. The file should be put under "resource/audios".
		/// name: The filename of the audio. (Including extension)
		/// return: The smart pointer of the sample.
		std::shared_ptr<ALLEGRO_SAMPLE> GetSample(std::string name);
		/// Get sample instance pointer by name. The file should be put under "resource/audios".
		/// name: The filename of the audio. (Including extension)
		/// return: The smart pointer of the sample instance.
		std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> GetSampleInstance(std::string name);
		/// Typical function to retrieve Singleton instance and supports lazy initialization.
		/// return: The Singleton instance of Resources.
		static Resources& GetInstance();
	};
}
#endif // RESOURCES_HPP
