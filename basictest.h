#pragma once

#include <string>

#include "itest.h"

namespace unit {
class BasicTest : public ITest {
    std::string name;
    bool passed;

public:
    BasicTest(const std::string &name);

    std::string getName();

    void report();

protected:
    void pass();
};
}
