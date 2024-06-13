#ifndef LOG_HPP
#define LOG_HPP
#include <fstream>
#include <iostream>

namespace Engine {
	// Log types that will be formatted in front of the line.
	enum LogType {
		VERBOSE,
		DEBUGGING,
		INFO,
		WARN,
		ERROR
	};

	/// Helper log class for quick logging to console and file. Can be used like std::cout.
	class LOG final {
	private:
		// Determine if global log is enabled.
		static bool Enabled;
		// Determine whether should log verbose messages or not.
		static bool LogVerbose;
		// The file path of the log file.
		static const char* FilePath;
		/// Get the label from log type.
		/// type: Log type of a log instance.
		/// return: the string label of the type.
		static const char* getLabel(LogType type);

		// File stream to write to.
		std::ofstream ofs;
		// Determines if log is enabled.
		bool enabled;

		/// Check should we log the message.
		/// return: Determines whether the messages should be logged.
		bool canLog() const;
	public:
		// Determines the prefix label.
		LogType type;

		/// Start a log chain with certain type.
		/// type: The type of this log chain, default is DEBUGGING.
		explicit LOG(LogType type = DEBUGGING);
		/// Add new line and close file.
		~LOG();
		/// Support logging chain that can be used in the same way as std::cout.
		template<class T>
		LOG& operator<<(const T &msg) {
			if (canLog()) {
				std::cout << msg;
				ofs << msg;
			}
			return *this;
		}
		/// Set global configuration.
		/// enabled: Determine if global log is enabled.
		/// logVerbose: Determine whether should log verbose messages or not.
		/// filePath: The file path of the log file.
		static void SetConfig(bool enabled = false, bool logVerbose = false, const char* filePath = "log.txt");
	};
}
#endif // LOGGER_HPP
