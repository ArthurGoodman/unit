#pragma once

#include <string>

#include "itest.h"

namespace unit {
class BasicTest : public ITest {
    std::string name;
    bool passed;
    unsigned short attributes;
    int maxNameLength;

public:
    BasicTest(const std::string &name);

    void align(int maxNameLength);

    std::string getName();
    void report();

protected:
    void pass();

private:
    void setConsoleColor(unsigned long color);
    void resetConsoleColor();
};
}
