#include "testbase.h"

#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <windows.h>

#define CONSOLE_COLOR_GREEN FOREGROUND_GREEN
#define CONSOLE_COLOR_RED FOREGROUND_RED
#elif __linux
#define CONSOLE_COLOR_GREEN 0
#define CONSOLE_COLOR_RED 1
#endif

unit::TestBase::TestBase(const std::string &name)
    : name(name)
    , passed(false)
    , maxNameLength(0) {
}

void unit::TestBase::align(int maxNameLength) {
    this->maxNameLength = maxNameLength;
}

std::string unit::TestBase::getName() {
    return name;
}

void unit::TestBase::report() {
    std::cout << name << std::setw(maxNameLength - (int)name.length() + 2) << " [";

    setConsoleColor(passed ? CONSOLE_COLOR_GREEN : CONSOLE_COLOR_RED);
    std::cout << (passed ? "OK" : "FAIL");
    resetConsoleColor();

    std::cout << "]" << std::endl;
}

void unit::TestBase::pass() {
    passed = true;
}

void unit::TestBase::setConsoleColor(unsigned long color) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    attributes = info.wAttributes;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
#elif __linux
    std::cout << "\033[0;" << (color == CONSOLE_COLOR_GREEN ? "32" : "31") << "m";
#endif
}

void unit::TestBase::resetConsoleColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
#elif __linux
    std::cout << "\033[0m";
#endif
}
