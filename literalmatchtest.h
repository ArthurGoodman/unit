#pragma once

#include <string>
#include <functional>

#include "functiontest.h"

namespace unit {
class LiteralMatchTest : public FunctionTest {
    std::string result;

public:
    LiteralMatchTest(const std::string &name, const std::string &result, const std::function<void()> &f);

    void run();
};
}
