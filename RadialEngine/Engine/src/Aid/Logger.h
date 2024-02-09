#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Core/Core.h"

enum class LogLevel {
    DISPLAY,
    NOTE,
    INFO,
    WARNING,
    ISSUE
};

class RE_API Logger {
public:

    static void Display(const std::string& message); // cyan // Used for quick debugging
    static void Note(const std::string& message);// white // General use, both debugging and non-important messages
    static void Info(const std::string& message);// green // Use for non-threatening messages such as common ocurances
    static void Warning(const std::string& message);// yellow // Used for uncertain behavior or destruction/deletion of objects
    static void Issue(const std::string& message); // red // Used for errors that will cause the program to crash or may cause unexpected behavior
    static void PrintScreen(const std::string& message);// Used to print to the console without color
private:

    static void PrintLog(LogLevel level, const std::string& message, WORD color);// Organizes the message and color to be printed to the console
};

/* Temp method to output a value ==> Logger::Note(std::to_string(940));
* this allows for the use of colors but having to convert to string is a bit annoying
* Optionally just use the ussual "std::cout << 940 << std::endl;" but this will not have colors
*/
/*TO DO::This logger has trouble dealing with some formats, as such needs replacement
*/