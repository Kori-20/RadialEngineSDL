#include "Logger.h"

void Logger::PrintLog(LogLevel level, const std::string& message, WORD color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleHandle, color);

    switch (level) {
	case LogLevel::DISPLAY:
		std::cout << message << std::endl;
		break;
    case LogLevel::NOTE:
        std::cout << "[NOTE] " << message << std::endl;
        break;
    case LogLevel::INFO:
        std::cout << "[INFO] " << message << std::endl;
        break;
    case LogLevel::WARNING:
        std::cerr << "[WARNING] " << message << std::endl;
        break;
    case LogLevel::ISSUE:
        std::cerr << "[ERROR] " << message << std::endl;
        break;

    default:
        std::cerr << "[ERROR] Invalid log level" << std::endl;
        break;
    }

    // Reset color to default
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::Display(const std::string& message)
{
    PrintLog(LogLevel::DISPLAY, message, FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void Logger::Note(const std::string& message) {
    PrintLog(LogLevel::NOTE, message, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::Info(const std::string& message) {
    PrintLog(LogLevel::INFO, message, FOREGROUND_GREEN);
}

void Logger::Warning(const std::string& message) {
    PrintLog(LogLevel::WARNING, message, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Logger::Issue(const std::string& message) {
    PrintLog(LogLevel::ISSUE, message, FOREGROUND_RED);
}

void Logger::PrintScreen(const std::string& message)
{

}
