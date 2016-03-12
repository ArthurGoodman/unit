#pragma once

#include <functional>

#include "basictest.h"

namespace unit {
class FunctionTest : public BasicTest {
    std::function<void()> f;

public:
    FunctionTest(const std::string &name, const std::function<void()> &f);

protected:
    std::string invoke();
};
}
