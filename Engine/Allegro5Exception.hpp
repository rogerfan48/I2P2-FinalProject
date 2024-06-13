#ifndef ALLEGRO5EXCEPTION_HPP
#define ALLEGRO5EXCEPTION_HPP
#include <stdexcept>
#include <string>

namespace Engine {
	/// Exception class dedicated to Allegro5 library's exception.
	class Allegro5Exception final : public std::runtime_error {
	public:
		/// Throw Allegro5 error with char array message.
		/// message: The error message.
		explicit Allegro5Exception(char const* const message) noexcept;
		/// Throw Allegro5 error with std::string message.
		/// message: The error message.
		explicit Allegro5Exception(const std::string& message) noexcept;
	};
}
#endif // ALLEGRO5EXCEPTION_HPP
