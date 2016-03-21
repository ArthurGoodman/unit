#pragma once

#include <functional>

#include "testbase.h"

namespace unit {
class FunctionTest;
}

class unit::FunctionTest : public TestBase {
    std::function<void()> f;

public:
    FunctionTest(const std::string &name, const std::function<void()> &f);

protected:
    std::string invoke();
};
