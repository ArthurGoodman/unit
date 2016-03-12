#include "basictest.h"

#include <iostream>
#include <windows.h>

unit::BasicTest::BasicTest(const std::string &name)
    : name(name), passed(false) {
}

std::string unit::BasicTest::getName() {
    return name;
}

void unit::BasicTest::report() {
    std::cout << name << " ";

    setConsoleColor(passed ? FOREGROUND_GREEN : FOREGROUND_RED);
    std::cout << (passed ? "OK" : "FAIL");
    resetConsoleColor();

    std::cout << std::endl;
}

void unit::BasicTest::pass() {
    passed = true;
}

void unit::BasicTest::setConsoleColor(unsigned long color) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    attributes = info.wAttributes;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
}

void unit::BasicTest::resetConsoleColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}
